#include "TextModule.hpp"

TextModule::TextModule()
{
   this->type = "TextModule"; 
   this->text = "";
}

TextModule::TextModule(uint128_t UUID){
   cout << "TextModule - constructor" << endl;
   this->type = "TextModule";
   this->text = "";
   this->command.push_back("UPDATE_TEXT");

   this->SetOnCommand("UPDATE_TEXT", [this] (string text) {this->updateText(text, false);});

}

void TextModule::updateText(string text, bool sync){
   cout << "TextModule - updateText" << endl;
   cout << text << endl;
   this->text = text;

   this->OnChange("UPDATE_TEXT", this->text);

   if( sync )
      this->outputFn(pair<string,string>{"UPDATE_TEXT" , this->text});
}

string TextModule::getText(){
   return this->text;
}

string TextModule::getState(){
   return this->getText();
}

void TextModule::setState(string state){
   this->updateText(state, false);
}