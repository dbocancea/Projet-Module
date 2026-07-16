#include "CameraModule.hpp"

int main( )
{

    uuids::random_generator gen;

    uuids::uuid UUID1 = gen( );

    CameraModule cam1 { UUID1 };

    // cout << UUID1 << "\n";

    cout << "Type: " << cam1.type << "\n";

    uuids::uuid UUID2 = gen( );

    CameraModule cam2 { UUID2 };

    uuids::uuid UUID3 = gen( );

    CameraModule cam3( UUID3 );

    cout << cam3.GetState() << "\n";

    // cout << UUID2 << "\n";

    return 0;
}