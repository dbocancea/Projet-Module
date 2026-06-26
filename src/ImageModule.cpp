#include "ImageModule.hpp"

ImageModule::ImageModule()
{
    this->type = "ImageModule";
}

ImageModule::ImageModule(uint128_t UUID) : TransformModule(UUID)
{
    this->type = "ImageModule";
    this->SetOnCommand("SET_IMAGE", [this](this->image)
    {
        this->setImage(image, false);
    });
}

string ImageModule::getImage()
{
    return this->image;
}

void ImageModule::setImage(string newIm, bool sync)
{
    this->image = newIm;
    this->OnChange("SET_IMAGE", this->image);

    if(sync)
    {
        cout << "SET_IMAGE " << this->image << endl;
    }
}

map<map<string, vector<float>>, string> ImageModule::getState()
{
    return {this->TransformModule::getState(), this->image};
}

void ImageModule::setState(map<string, vector<float>> state)
{
    this->TransformModule::setState(state);
    this->setImage(state->first);
}
