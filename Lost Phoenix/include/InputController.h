#pragma once

enum class Key 
{
	W, A, S, D, Space, Size
};

class InputController
{
public:
	InputController( );

	void updateInput( );
	bool isKeyDown(Key key);

private:
	static int KeysEnum[(int)Key::Size];
	bool m_KeyState[(int)Key::Size];

};