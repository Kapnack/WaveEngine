#include "ImGuiClassState.h"

int ImGuiClassState::ResizeCallback(ImGuiInputTextCallbackData* data)
{
    {
        if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
        {
            auto* str = static_cast<std::string*>(data->UserData);
            str->resize(data->BufTextLen);
            data->Buf = str->data();
        }

        return 0;
    }

}

ImGuiClassState::ImGuiClassState()
{
}

ImGuiClassState::~ImGuiClassState()
{
}
