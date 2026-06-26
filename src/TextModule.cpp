#include "TextModule.hpp"

TextModule::TextModule()
{
   this->type = "TextModule"; 
}

TextModule::TextModule(uint128_t UUID) : ModuleCore(UUID)
{
	cout << "TextModule - constructor" << endl;
	this->type = "TextModule";
	this->command.push_back("UPDATE_TEXT");

	this->SetOnCommand("UPDATE_TEXT", [&](string text) {this->UpdateText(text, 0); })
}

void TextModule::UpdateText(string text; bool sync)
{
	cout << "TextModule - updateText" << endl;
	cout << text << endl;
	this->text = text;
	this->OnChange("UPDATE_TEXT", this->text);

	if( sync )
		this->outputFn(pair<string, string >{"UPDATE_FILE", this->text});
}

string TextModule::GetText()
{
	return this->text;
}

string TextModule::GetState()
{
	return this->text;
}

void TextModule::SetState(string state)
{
	this->UpdateText(state, 0);
}
