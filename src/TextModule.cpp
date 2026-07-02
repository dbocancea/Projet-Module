#include "TextModule.hpp"
namespace json = boost::json;

TextModule::TextModule()
{
   this->type = "TextModule"; 
   this->text = "";
}

TextModule::TextModule(uint128_t UUID) : ModuleCore(UUID){
   cout << "TextModule - constructor" << endl;
   this->type = "TextModule";
   this->text = "";
   this->command.push_back("UPDATE_TEXT");

   this->SetOnCommand("UPDATE_TEXT", [this] (json::value textJson) 
   {
      string text = textJson.as_object().at("text").as_string().c_str();
      this->updateText(text,false);
   });

}

void TextModule::updateText(string text, bool sync){
   cout << "TextModule - updateText" << endl;
   cout << text << endl;
   this->text = text;

   this->OnChange("UPDATE_TEXT", json::value(this->text));

   if( sync ){
      json::object data;
      data["text"] = this->text;
      this->Output("UPDATE_TEXT" , data);
   }
}

string TextModule::getText(){
   return this->text;
}

json::value TextModule::getState(){
   json::object state;
   state["text"] = this->text;
   return state;
}

void TextModule::setState(json::value state){
   this->updateText(state.as_object().at("text").as_string().c_str(), false);
}