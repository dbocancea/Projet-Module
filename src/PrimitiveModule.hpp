#ifndef PRIMITIVEMODULE_HPP
#define PRIMITIVEMODULE_HPP
#include "TransformModule.hpp"

class PrimitiveModule : public TransformModule
{
    protected:
        json::value primitiveTypes;
        json::value primitive;
    public:
        PrimitiveModule( );
        PrimitiveModule( uint128_t UUID );
        json::value getPrimitive( );
        json::value getPrimitiveTypes( );
        void onUpdatePrimitive( json::value primitive, bool sync = false );
        void updatePrimitive( json::value primitive, bool sync = false );
        json::value getState( );
        void setState( json::value state );
};
  
#endif