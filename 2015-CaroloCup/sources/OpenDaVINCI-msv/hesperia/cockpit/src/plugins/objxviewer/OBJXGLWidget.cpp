/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <fstream>

#include "core/macros.h"
#include "core/base/Lock.h"
#include "core/io/URL.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/TransformGroup.h"
#include "hesperia/threeD/decorator/DecoratorFactory.h"
#include "hesperia/threeD/models/Grid.h"
#include "hesperia/threeD/models/XYZAxes.h"
#include "hesperia/threeD/loaders/OBJXArchive.h"
#include "hesperia/threeD/loaders/OBJXArchiveFactory.h"

#include "plugins/objxviewer/OBJXGLWidget.h"

namespace cockpit {
    namespace plugins {
        namespace objxviewer {

            using namespace std;
            using namespace core::base;
            using namespace core::io;
            using namespace hesperia::threeD;
            using namespace hesperia::threeD::decorator;
            using namespace hesperia::threeD::loaders;
            using namespace hesperia::threeD::models;

            OBJXGLWidget::OBJXGLWidget(const PlugIn &plugIn, QWidget *prnt) :
                    AbstractGLWidget(plugIn, prnt),
                    m_root(NULL),
                    m_modelMutex(),
                    m_model(NULL) {}

            OBJXGLWidget::~OBJXGLWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_root);
            }

            void OBJXGLWidget::setOBJXModel(const string &objxModel) {
                Lock l(m_modelMutex);
                m_model->deleteAllChildren();

                fstream fin(objxModel.c_str(), ios::in | ios::binary);

                if (fin.good()) {
                    OBJXArchive *objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchive(fin);

                    fin.close();

                    if (objxArchive != NULL) {
                        // Decorate objxArchive for getting displayed in an OpenGL scene.
                        Node *n = DecoratorFactory::getInstance().decorate(*objxArchive, NodeDescriptor(objxModel));

                        if (n != NULL) {
                            m_model->addChild(n);
                        } else {
                            cout << "Model could not be loaded." << endl;
                        }

                        OPENDAVINCI_CORE_DELETE_POINTER(objxArchive);
                    }
                } else {
                    cout << "File could not be opened." << endl;
                }
            }

            void OBJXGLWidget::setupOpenGL() {
                glEnable(GL_LIGHTING);

                glEnable(GL_LIGHT0);
                float light0Position[4] = {0, 0, 20, 0};
                float light0Ambient[4] = {0.5f, 0.5f, 0.5f, 0};
                float light0Diffuse[4] = {0.8f, 0.8f, 0.8f, 0};
                float light0Specular[4] = {0, 0, 0, 0};
                glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
                glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
                glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
            }

            void OBJXGLWidget::initScene() {
                Lock l(m_modelMutex);

                // Initialize.
                m_model = new TransformGroup();

                TransformGroup *tg = new TransformGroup();
                // Add model to be shown.
                tg->addChild(m_model);

                tg->addChild(new XYZAxes(NodeDescriptor("XYZAxes"), 1, 12));
                tg->addChild(new Grid(NodeDescriptor("Grid"), 10, 1));

                m_root = tg;
            }

            void OBJXGLWidget::drawScene() {
                Lock l(m_modelMutex);
                if (m_root != NULL) {
                    RenderingConfiguration r = RenderingConfiguration();
                    m_root->render(r);
                }
            }
        }
    }
} // cockpit::plugins::objxviewer
