#include "PrimitiveModule.hpp"

PrimitiveModule::PrimitiveModule( ) : TransformModule( )
{
    this->type = "PrimitiveModule";
    this->primitive = "sphere";
    this->primitiveTypes = {this->primitive, "box"};
}

PrimitiveModule::PrimitiveModule( uuids::uuid UUID ) : TransformModule( UUID )
{
    this->type = "PrimitiveModule";

    this->primitive = "sphere";
    this->primitiveTypes = {this->primitive, "box"};

    this->SetOnCommand( "UPDATE_PRIMITIVE", [this]( json::value primitive )
    {
        this->onUpdatePrimitive( primitive );
    });
}

json::value PrimitiveModule::getPrimitive( )
{
    return this->primitive;
}

json::value PrimitiveModule::getPrimitiveTypes( )
{
    return this->primitiveTypes;
}

void PrimitiveModule::onUpdatePrimitive( json::value primitive_update, bool sync )
{
    if( !primitive_update.is_string( ) ) return;
    this->primitive = primitive_update;

    this->updatePrimitive( primitive_update, sync );
}

void PrimitiveModule::updatePrimitive( json::value primitive_update, bool sync )
{
    this->OnChange( "UPDATE_PRIMITIVE", primitive_update );

    if( sync )
        this->Output( "UPDATE_PRIMITIVE", primitive_update );
}

json::value PrimitiveModule::GetState( )
{
    json::value transformState = this->TransformModule::GetState( );
    json::object obj = transformState.as_object( );

    obj["primitive"] = this->primitive;

    return obj;
}

void PrimitiveModule::SetState( json::value state )
{
    if( !state.is_object( ) ) return;

    auto& obj = state.as_object();
    auto it = obj.find( "primitive" );
    if( it != obj.end() )
        this->onUpdatePrimitive( it->value() );

    this->TransformModule::SetState(state);
}
