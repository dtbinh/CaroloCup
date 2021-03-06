/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include "hesperia/threeD/models/XYZAxes.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            XYZAxes::XYZAxes(const NodeDescriptor &nodeDescriptor) :
                    Node(nodeDescriptor),
                    m_lineWidth(1),
                    m_lineLength(2) {}

            XYZAxes::XYZAxes(const NodeDescriptor &nodeDescriptor, const float &lineWidth, const float &lineLength) :
                    Node(nodeDescriptor),
                    m_lineWidth(lineWidth),
                    m_lineLength(lineLength) {}

            XYZAxes::XYZAxes(const XYZAxes &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_lineWidth(obj.m_lineWidth),
                    m_lineLength(obj.m_lineLength) {}

            XYZAxes::~XYZAxes() {}

            XYZAxes& XYZAxes::operator=(const XYZAxes &obj) {
                setNodeDescriptor(obj.getNodeDescriptor()),
                m_lineWidth = obj.m_lineWidth;
                m_lineLength = obj.m_lineLength;
                return (*this);
            }

            void XYZAxes::render(RenderingConfiguration &renderingConfiguration) {
                // Render if unnamed or not disabled.
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        glLineWidth(m_lineWidth);
                        glColor3f(1, 1, 1);

                        glBegin(GL_LINES);
                        // X-axis.
                        glVertex3f(0, 0, 0);
                        glVertex3f(m_lineLength, 0, 0);

                        // Arrow.
                        glVertex3f(m_lineLength, 0, 0);
                        glVertex3f((m_lineLength - 0.1f), 0.1f, 0);

                        glVertex3f(m_lineLength, 0, 0);
                        glVertex3f((m_lineLength - 0.1f), -0.1f, 0);

                        // X-label.
                        glVertex3f(-0.3f + (m_lineLength - 0.1f), -0.3f + 0.1f, 0);
                        glVertex3f(-0.3f + (m_lineLength + 0.1f), -0.3f + -0.1f, 0);

                        glVertex3f(-0.3f + (m_lineLength + 0.1f), -0.3f + 0.1f, 0);
                        glVertex3f(-0.3f + (m_lineLength - 0.1f), -0.3f + -0.1f, 0);

                        // Y-axis
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, m_lineLength, 0);

                        // Arrow.
                        glVertex3f(0, m_lineLength, 0);
                        glVertex3f(0.1f, (m_lineLength - 0.1f), 0);

                        glVertex3f(0, m_lineLength, 0);
                        glVertex3f(-0.1f, (m_lineLength - 0.1f), 0);

                        // Y-label.
                        glVertex3f(-0.3f + -0.1f, m_lineLength, 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);

                        glVertex3f(-0.3f + 0.1f, m_lineLength, 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);

                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.2f), 0);

                        // Z-axis
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, 0, m_lineLength);

                        // Arrow.
                        glVertex3f(0, 0, m_lineLength);
                        glVertex3f(0.1f, 0, (m_lineLength - 0.1f));

                        glVertex3f(0, 0, m_lineLength);
                        glVertex3f(-0.1f, 0, (m_lineLength - 0.1f));

                        // Z-label.
                        glVertex3f(-0.3f + -0.1f, 0, m_lineLength);
                        glVertex3f(-0.3f + 0.1f, 0, m_lineLength);

                        glVertex3f(-0.3f + 0.1f, 0, m_lineLength);
                        glVertex3f(-0.3f + -0.1f, 0, (m_lineLength - 0.1f));

                        glVertex3f(-0.3f + -0.1f, 0, (m_lineLength - 0.1f));
                        glVertex3f(-0.3f + 0.1f, 0, (m_lineLength - 0.1f));
                        glEnd();

                        glLineWidth(1);
                    }

                    glPopMatrix();
                }
            }

        }
    }
} // core::threeD::models
