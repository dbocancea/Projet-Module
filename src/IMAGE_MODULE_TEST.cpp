// #include "ImageModule.hpp"

// int main( )
// {
//     uuids::random_generator gen;

//     uuids::uuid UUID = gen( );

//     ImageModule im1 { UUID };

//     cout << "Type: " << im1.type << "\n";

//     cout << "Command: " << im1.GetCommand( )[ "setImage" ] << "\n";

//     json::object image_input;

//     image_input[ "image" ] = "https://img.magnific.com/photos-gratuite/gros-plan-beau-papillon-textures-interessantes-fleur-petale-orange_181624-7640.jpg?semt=ais_hybrid&w=740&q=80";

//     json::object trans_data;

//     trans_data[ "translation" ] = { 0.0, 0.0, 0.0 };
//     trans_data[ "rotation" ] = { 0.0, 0.0, 0.0, 0.0 };
//     trans_data[ "scale" ] = { 0.0, 0.0, 0.0 };

//     image_input[ "transform" ] = trans_data;

//     im1.SetState( image_input );

//     json::value res = im1.GetState( );

//     cout << res << "\n";



//     return 0;
// }