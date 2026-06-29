#include "ImageModule.hpp"

ImageModule::ImageModule() : TransformModule(0)
{
    this->type = "ImageModule";
}

ImageModule::ImageModule(uint128_t UUID) : TransformModule(UUID)
{
    this->type = "ImageModule";
    this->SetOnCommand("SET_IMAGE", [this](string image)
    {
        this->setImage(image);
    });
}

string ImageModule::getImage()
{
    return this->image;
}

void ImageModule::setImage(string newIm, bool sync)
{
    this->image = newIm;
    this->OnChange("SET_IMAGE", newIm);

    if(sync)
    {
        cout << "SET_IMAGE " << this->image << endl;
    }
}

map<string, map<string, vector<float>>> ImageModule::getState()
{
    map<string, map<string, vector<float>>> res {};
    res[this->image] = this->TransformModule::getState();
    return res;
}

void ImageModule::setState(map<string, map<string, vector<float>>> state)
{
    auto it = state.begin();

    this->setImage(it->first);
    this->TransformModule::setState(it->second);
}


void ImageModule::OnChange(string cmd, string data)
{
    auto it = this->stringChangeCallBack.find(cmd);
    if(it != this->stringChangeCallBack.end())
    {
        for(auto& tmp : it->second)
        {
            tmp(data);
        }
    }
    else
    {
        cout << this->UUID << " no member " << endl;
    }
}

void ImageModule::SetOnCommand(string cmd, function<void(string)> callBack)
{
    this->stringCommandCallBack[cmd].push_back(callBack);
}


void ImageModule::OnCommand(string cmd, string data)
{
    auto it = this->stringCommandCallBack.find(cmd);
    if(it != this->stringCommandCallBack.end())
    {
        for(auto& tmp : it->second)
        {
            tmp(data);
        }
    }
    else
    {
        cout << this->UUID << " no member " << endl;
    }
}
