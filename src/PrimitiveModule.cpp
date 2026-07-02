#include "PrimitiveModule.hpp"

PrimitiveModule::PrimitiveModule() : TransformModule(0)
{
    this->type = "PrimitiveModule";
    this->primitive = "sphere";
    this->primitiveTypes = {this->primitive, "box"};
}

PrimitiveModule::PrimitiveModule( uint128_t UUID ) : TransformModule( UUID )
{
    this->type = "PrimitiveModule";

    this->primitive = "sphere";
    this->primitiveTypes = {this->primitive, "box"};

    this->SetOnCommand("UPDATE_PRIMITIVE", [this](json::value primitive)
    {
        this->updatePrimitive(this->primitive);
    });
}

json::value PrimitiveModule::getPrimitive()
{
    return this->primitive;
}

json::value PrimitiveModule::getPrimitiveTypes()
{
    return this->primitiveTypes;
}

void PrimitiveModule::updatePrimitive( json::value primitive, bool sync )
{
    if( !primitive.is_object() ) return;
    this->primitive = primitive;

    this->OnChange( "UPDATE_PRIMITIVE", this->primitive );

    if( sync )
        this->Output( "UPDATE_PRIMITIVE", this->primitive);
}

json::value PrimitiveModule::getState()
{
    json::value transformState = this->TransformModule::getState();
    json::object obj = transformState.as_object();

    obj["primitive"] = this->primitive;

    return obj;
}

void PrimitiveModule::setState( json::value state )
{
    if( !state.is_object() ) return;

    auto& obj = state.as_object();
    auto it = obj.find( "primitive" );
    if( it != obj.end() )
        this->updatePrimitive( it->value() );

    this->TransformModule::setState(state);
}
