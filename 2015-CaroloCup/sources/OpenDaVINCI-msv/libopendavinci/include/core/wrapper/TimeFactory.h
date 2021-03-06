/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef OPENDAVINCI_CORE_WRAPPER_TIMEFACTORY_H_
#define OPENDAVINCI_CORE_WRAPPER_TIMEFACTORY_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/wrapper/Libraries.h"
#include "core/wrapper/ConfigurationTraits.h"
#include "core/wrapper/StaticInstanceFactory.h"
#include "core/wrapper/Mutex.h"

#include "core/wrapper/TimeFactoryWorker.h"

#ifdef WIN32
    #include "core/wrapper/WIN32/WIN32TimeFactoryWorker.h"
#endif
#ifndef WIN32
    #include "core/wrapper/POSIX/POSIXTimeFactoryWorker.h"
#endif

namespace core {
    namespace wrapper {

        /**
         * Factory for creating wrapped times (i.e.
         * time data structures based on Win32, POSIX, ...).
         *
            * It can be used as follows:
            *
            * @code
            * Time *t = TimeFactory::getInstance().now();
            *
            * ...
            *
            * if (t != NULL) {
            *     delete t;
            * }
            *
            * @endcode
         */
        class OPENDAVINCI_API TimeFactory {
            public:
                virtual ~TimeFactory() {};
                virtual Time* now();
                static TimeFactory& getInstance();

            protected:
                TimeFactory();
                static void setSingleton(TimeFactory *tf);
                static TimeFactory *instance;
                static TimeFactory *controlledInstance;

            private:
                static Mutex *m_singletonMutex;
        };

        class OPENDAVINCI_API SystemTimeFactory
        {
            public:
                // Product type created by factory.
                typedef SystemLibraryProducts product_type;

                // Configuration for factory.
                typedef ConfigurationTraits<product_type>::configuration configuration_value;

                // Factory method to create a concrete product
                typedef TimeFactoryWorker<configuration_value::value> worker_type;

                // Wrapper to preserve current functionality.
                static worker_type getInstance() { return instance; }

            protected:
                // Wrapper to preserve current functionality.
                static worker_type instance;
        };

    }
} // core::wrapper

#endif /*OPENDAVINCI_CORE_WRAPPER_TIMEFACTORY_H_*/
