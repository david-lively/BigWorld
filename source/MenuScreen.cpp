#include "MenuScreen.h"

#include "Vertex.h"
#include "Buffer.h"
#include "GeometryProvider.h"
#include "Mesh.h"
#include "Effect.h"
#include "GameTime.h"
#include "Console.h"

#include <vector>

using namespace std;


MenuScreen::MenuScreen()
{
}


MenuScreen::~MenuScreen()
{
}


void MenuScreen::OnLoad()
{
	CreateScene();
}


void MenuScreen::CreateScene()
{
	vector<VertexPosition> vertices;
	vector<int> indices;

	check_gl_error();

	GeometryProvider::Quad(vertices, indices);

	auto& quad = Create<GameObject>("debug-quad");
	auto& mesh = quad.Create<Mesh<VertexPosition,int>>("debug-quad-mesh");

    m_effect = &quad.Create<Effect>("primitive");
    m_effect->Rebuild();
    m_effect->Bind();
    
    Global::InitializeUniformMap(m_effect->Handle);
    
    Global::SetUniform("World",Matrix4::Identity());
    Global::SetUniform("View",Matrix4::Identity());
    Global::SetUniform("Projection",Matrix4::Identity());
    
	mesh.SetData(vertices, indices);

	check_gl_error();
    
    //auto& console = Create<Console>("console.global");
//    console << "Hello world!";

}

void MenuScreen::OnRender(const GameTime& time)
{
    Global::SetUniform("GameTimeTotalSeconds",time.TotalSeconds());
    
    GameObject::OnRender(time);
}

