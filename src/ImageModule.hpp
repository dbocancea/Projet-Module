#ifndef IMAGE_MODULE_HPP
#define IMAGE_MODULE_HPP
#include "TransformModule.hpp"

class ImageModule : public TransformModule
{
    protected:
        string image;
        map<std::string, vector<function<void(json::value)>>> stringCommandCallBack;
        map<std::string, vector<function<void(json::value)>>> stringChangeCallBack;
    public:
        ImageModule();
        ImageModule(uint128_t UUID);
        json::value getImage();
        void setImage(json::value image, bool sync = false);
        json::value getState();
        void setState(json::value state);
};

#endif