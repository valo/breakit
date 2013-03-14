bin_PROGRAMS = breakin
breakin_SOURCES = breakin.cpp CAllegroDisplay.h CAllegroDisplay.cpp CBreakinOnePlayer.h CBreakinOnePlayer.cpp CBall.h CBall.cpp CBlockMap.h CBlockMap.cpp CPlayer.h CPlayer.cpp CBlock.h CBlock.cpp CMasterofPuppets.h CMasterofPuppets.cpp CObject.h CObject.cpp CBonus.h CBonus.cpp CList.cpp CList.h CFlyingText.cpp CFlyingText.h defines.h CMainMenu.h CMainMenu.cpp CComponent.h CComponent.cpp CButton.h CButton.cpp CEditField.h CEditField.cpp CPanel.h CPanel.cpp CMedia.h CMedia.cpp CHallOfFame.h CHallOfFame.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
breakin_LDFLAGS = $(all_libraries) `allegro-config --static release`
breakin_LDADD = /usr/local/lib/libalfont.a
