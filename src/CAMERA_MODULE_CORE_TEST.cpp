#include "CameraModule.hpp"

int main( )
{

    uuids::random_generator gen;

    uuids::uuid UUID = gen( );

    CameraModule cam1 { UUID };

    cout << "Type: " << cam1.type << "\n";

    return 0;
}