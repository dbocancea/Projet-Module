#ifndef IMAGE_MODULE_HPP
#define IMAGE_MODULE_HPP
#include "TransformModule.hpp"

class ImageModule : public TransformModule<string>
{
    protected:
        string image;
        map<std::string, vector<function<void(string)>>> stringCommandCallBack;
    public:
        ImageModule();
        ImageModule(uint128_t UUID);
        string getImage();
        void setImage(string image, bool sync = false);
        map<string, map<string, vector<float>>> getState();
        void setState(map<string, map<string, vector<float>>> state);

        void SetOnCommand(string cmd, function<void(string)> callBack);
        void OnCommand(string cmd, string data);
};

#endif