#pragma once

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnRender() {};
	virtual void OnUpdate() {};



};

class Dockspace : public Layer
{
public:
    virtual void OnRender() override;
};


class MenuBar : public Layer
{
public:
	virtual void OnRender() override;
};

