/*
 Copyright (c) 2014, The Cinder Project, All rights reserved.

 This code is intended for use with the Cinder C++ library: http://libcinder.org

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "cinder/app/AppBasic.h"

namespace cinder { namespace app {

class AppImplMswBasic;

class AppBasicMsw : public AppBasic {
  public:
	//! MSW-specific settings
	class Settings : public AppBasic::Settings {
	  public:
		Settings() : mEnableMswConsole( false )				{}

		//! If enabled MSW apps will display a secondary window which captures all cout, cerr, cin and App::console() output. Default is \c false.
		void	enableConsoleWindow( bool enable = true )	{ mEnableMswConsole = enable; }
		//! Returns whether MSW apps will display a secondary window which captures all cout, cerr, cin and App::console() output. Default is \c false.
		bool	isConsoleWindowEnabled() const				{ return mEnableMswConsole; }

	  private:
		bool		mEnableMswConsole;
	};

	AppBasicMsw();
	virtual ~AppBasicMsw();

	WindowRef	createWindow( const Window::Format &format ) override;
	void		quit() override;

	float		getFrameRate() const override;
	void		setFrameRate( float frameRate ) override;
	void		disableFrameRate() override;
	bool		isFrameRateEnabled() const override;
	fs::path	getAppPath() const override;

	WindowRef	getWindow() const override;
	WindowRef	getWindowIndex( size_t index ) const override;
	size_t		getNumWindows() const override;

	WindowRef	getForegroundWindow() const override;

	void		hideCursor() override;
	void		showCursor() override;
	ivec2		getMousePos() override;

	fs::path getOpenFilePath( const fs::path &initialPath, const std::vector<std::string> &extensions ) override;
	fs::path getFolderPath( const fs::path &initialPath ) override;
	fs::path getSaveFilePath( const fs::path &initialPath, const std::vector<std::string> &extensions ) override;

	const Settings&	getSettings() const override	{ return mSettings; }

	//! \cond
	// Called by app instantiation macro during launch process
	static void	executeLaunch( AppBasic *app, RendererRef renderer, const char *title );
	//! \endcond

  protected:
	void	launch( const char *title, int argc, char * const argv[] ) override;

  private:
	AppImplMswBasic*	mImpl;
	Settings			mSettings;
};

#define CINDER_APP_BASIC_MSW( APP, RENDERER )														\
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )	\
{																									\
	cinder::app::AppBasic::prepareLaunch();															\
	cinder::app::RendererRef defaultRenderer( new RENDERER );										\
	cinder::app::App::initialize( defaultRenderer );												\
	cinder::app::AppBasic *app = new APP;															\
	cinder::app::App::executeLaunch( #APP, 0, nullptr );											\
	cinder::app::AppBasic::cleanupLaunch();															\
	return 0;																						\
}

} } // namespace cinder::app
