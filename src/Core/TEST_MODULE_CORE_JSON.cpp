#include "ModuleCoreJson.hpp"

int main()
{
    ModuleCore mod1( 1234 );
    ModuleCore mod2( 5678 );

    mod1.SetOnCommand( "ADD", [&]( json::value data )
    {
        cout << "Add command has been added" << endl;

        mod1.OnChange( "ADD cmd ADD mod1", data );

        if( mod1.outputFn )
            mod1.outputFn( data );
    });

    mod1.SetOnChange( "ADD cmd ADD mod1", [&]( json::value data )
    {
        cout << "Event ADD is working!" << endl;
    });

    mod2.SetOnCommand( "SMT", [&]( json::value data )
    {
        cout << "Add command SMT" << endl;

        mod2.OnChange( "SMT_ADD", data );
    });

    mod2.SetOnChange( "SMT_ADD", [&] ( json::value data ) 
    {
        cout << "Event SMT_ADD is working" << endl;
    });

    mod1.SetOutputFn([&]( json::value data )    
    {
        cout << "mod1 and mod2 are connecting" << endl;

        mod2.OnCommand( "SMT", data );
    });

    cout << "test" << endl;

    json::value test_json = json::object();

    mod1.OnCommand("ADD", test_json);

    return 0;
}