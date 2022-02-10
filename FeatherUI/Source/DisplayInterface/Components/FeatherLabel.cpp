#include <FeatherUI/DisplayInterface/Components/FeatherLabel.h>
#include <FeatherUI/DisplayInterface/Components/FeatherContainer.h>

FeatherLabel::FeatherLabel(const int x, const int y, ID3DXFont* font, const std::string& labelText, const DWORD color,
	const ALIGN_LABEL align)
{
	FeatherComponent::SetPosition(x, y);

	this->labelFont = font;
	this->labelText = labelText;
	this->color = color;
	this->width = GetTextWidth();
	this->height = GetTextHeight();
	this->labelAlign = align;
}

FeatherLabel::FeatherLabel(int x, int y, ID3DXFont* font, const std::wstring& labelText, DWORD color,
	FeatherLabel::ALIGN_LABEL align)
{
	FeatherComponent::SetPosition(x, y);

	this->labelFont = font;
	this->labelTextW = labelText;
	this->color = color;
	this->width = GetTextWidth();
	this->height = GetTextHeight();
	this->labelAlign = align;
}


void FeatherLabel::Render()
{
	if (labelText)
		switch (labelAlign)
		{
		case LEFT:
			g_render.StringA(labelFont, this, DT_LEFT, false, color, labelText->c_str());
			break;
		case CENTER:
			g_render.StringA(labelFont, this, DT_CENTER, false, color, labelText->c_str());
			break;
		case RIGHT:
			g_render.StringA(labelFont, this, DT_RIGHT, false, color, labelText->c_str());
			break;
		}
	else
		switch (labelAlign)
		{
		case LEFT:
			g_render.StringW(labelFont, this, DT_LEFT, false, color, labelTextW->c_str());
			break;
		case CENTER:
			g_render.StringW(labelFont, this, DT_CENTER, false, color, labelTextW->c_str());
			break;
		case RIGHT:
			g_render.StringW(labelFont, this, DT_RIGHT, false, color, labelTextW->c_str());
			break;
		}
}

void FeatherLabel::SetLabelAlign(const ALIGN_LABEL align)
{
	labelAlign = align;
}

void FeatherLabel::SetLabelFont(ID3DXFont* font)
{
	labelFont = font;
}

void FeatherLabel::SetLabelText(const std::string& labelText)
{
	this->labelText = labelText;
}

void FeatherLabel::SetLabelText(const std::wstring& labelText)
{
	this->labelTextW = labelText;
}

void FeatherLabel::SetTextHeight(const int height)
{
	this->height = height;
}

void FeatherLabel::SetTextWidth(const int width)
{
	this->width = width;
}

int FeatherLabel::GetTextWidth()
{
	if (labelText)
		return g_render.GetTextWidth(labelText.value(), labelFont);

	return g_render.GetTextWidth(labelTextW.value(), labelFont);
}

void FeatherLabel::ResetTextWidth()
{
	this->width = GetTextWidth();
}

int FeatherLabel::GetTextHeight()
{
	if (labelText)
		return RenderEngine::GetTextHeight(labelText.value(), labelFont);

	return RenderEngine::GetTextHeight(labelTextW.value(), labelFont);
}

void FeatherLabel::ResetTextHeight()
{
	this->height = GetTextHeight();
}

std::string& FeatherLabel::GetLabelText()
{
	return labelText.value();
}