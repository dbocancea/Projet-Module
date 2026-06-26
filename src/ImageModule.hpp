#ifndef IMAGE_MODULE_HPP
#define IMAGE_MODULE_HPP
#include "TransformModule.hpp"

class ImageModule : public TransformModule
{
    protected:
        string image;
    public:
        ImageModule();
        ImageModule(uint128_t UUID);
        string getImage();
        void setImage(string image, bool sync);
        map<string, map<string, vector<float>>> getState();
        void setState(map<string, vector<float>> state);
}

#endif