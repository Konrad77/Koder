/*
 * Koder is a code editor for Haiku based on Scintilla.
 *
 * Copyright (C) 2014-2015 Kacper Kasper <kacperkasper@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <MimeType.h>
#include <Statable.h>
#include <String.h>
#include <Window.h>

#include <ScintillaView.h>

#include "Languages.h"


struct entry_ref;
class BFilePanel;
class BMenu;
class BMenuBar;
class BPath;
class Editor;
class GoToLineWindow;
class Preferences;
class Styler;


const BString gAppName = "Koder";
const BString gAppMime = "application/x-vnd.KapiX-Koder";

const uint32 ACTIVE_WINDOW_CHANGED = 'AWCH';


enum {
	MAINMENU_FILE_NEW					= 'mnew',
	MAINMENU_FILE_OPEN					= 'mopn',
	MAINMENU_FILE_SAVE					= 'msav',
	MAINMENU_FILE_SAVEAS				= 'msva',
	MAINMENU_FILE_QUIT					= 'mqut',

	MAINMENU_EDIT_CONVERTEOLS_UNIX		= 'ceun',
	MAINMENU_EDIT_CONVERTEOLS_WINDOWS	= 'cewi',
	MAINMENU_EDIT_CONVERTEOLS_MAC		= 'cema',

	MAINMENU_EDIT_FILE_PREFERENCES		= 'mefp',
	MAINMENU_EDIT_APP_PREFERENCES		= 'meap',

	MAINMENU_VIEW_SPECIAL_WHITESPACE	= 'vsws',
	MAINMENU_VIEW_SPECIAL_EOL			= 'vseo',

	MAINMENU_SEARCH_FINDREPLACE			= 'msfr',
	MAINMENU_SEARCH_GOTOLINE			= 'msgl',

	MAINMENU_VIEW_LINEHIGHLIGHT			= 'mlhl',
	MAINMENU_VIEW_LINENUMBERS			= 'mvln',

	MAINMENU_LANGUAGE					= 'ml00',

	FILE_OPEN							= 'flop',
	FILE_SAVE							= 'flsv',

	WINDOW_NEW							= 'ewnw',
	WINDOW_CLOSE						= 'ewcl',
};


class EditorWindow : public BWindow {
public:
							EditorWindow();

			void			New();
			void			OpenFile(entry_ref* ref);
			void			RefreshTitle();
			void			SaveFile(entry_ref* ref);

			bool			QuitRequested();
			void			MessageReceived(BMessage* message);
			void			WindowActivated(bool active);

	static	void			SetPreferences(Preferences* preferences);
	static	void			SetStyler(Styler* styler);

private:
	enum ModifiedAlertResult {
		CANCEL	= 0,
		DISCARD	= 1,
		SAVE	= 2
	};
			BMenuBar*		fMainMenu;
			BPath*			fOpenedFilePath;
			BMimeType		fOpenedFileMimeType;
			time_t			fOpenedFileModificationTime;
			bool			fModifiedOutside;
			bool			fModified;
			bool			fReadOnly;
			Editor*			fEditor;
			BFilePanel*		fOpenPanel;
			BFilePanel*		fSavePanel;
			BMenu*			fLanguageMenu;

			Sci_Position	fSearchTargetStart;
			Sci_Position	fSearchTargetEnd;
			Sci_Position	fSearchLastResultStart;
			Sci_Position	fSearchLastResultEnd;

			GoToLineWindow*	fGoToLineWindow;

			bool			fActivatedGuard;

	static	Preferences*	fPreferences;
	static	Styler*			fStyler;

			bool			_CheckPermissions(BStatable* file, mode_t permissions);
			void			_FindReplace(BMessage* message);
			status_t		_MonitorFile(BStatable* file, bool enable);
			void			_PopulateLanguageMenu(BMenu* languageMenu);
			void			_ReloadFile(entry_ref* ref = nullptr);
			void			_SetLanguage(LanguageType lang);
			void			_SetLanguageByFilename(const char* filename);
			void			_SyncWithPreferences();
			int32			_ShowModifiedAlert();
			void			_Save();
};


#endif // EDITORWINDOW_H
