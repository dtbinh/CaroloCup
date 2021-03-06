/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_DATA_ENVIRONMENT_EGOSTATE_H_
#define HESPERIA_DATA_ENVIRONMENT_EGOSTATE_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "hesperia/data/environment/PointShapedObject.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace core::data::environment;

            /**
             * This class contains all relevant data for the own car.
             */
            class OPENDAVINCI_API EgoState : public PointShapedObject {
                public:
                    EgoState();

                    /**
                     * Constructor.
                     *
                     * @param position Position.
                     * @param rotation Rotation.
                     * @param velocity Velocity.
                     * @param acceleration Acceleration.
                     */
                    EgoState(const Point3 &position, const Point3 &rotation,
                             const Point3 &velocity, const Point3 &acceleration);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    EgoState(const EgoState &obj);

                    virtual ~EgoState();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    EgoState& operator=(const EgoState &obj);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;
            };

        }
    }
} // hesperia::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_EGOSTATE_H_*/
