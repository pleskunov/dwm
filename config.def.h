/* See LICENSE file for copyright and license details. */

/*
██████╗ ██╗    ██╗███╗   ███╗
██╔══██╗██║    ██║████╗ ████║
██║  ██║██║ █╗ ██║██╔████╔██║
██║  ██║██║███╗██║██║╚██╔╝██║
██████╔╝╚███╔███╔╝██║ ╚═╝ ██║
╚═════╝  ╚══╝╚══╝ ╚═╝     ╚═╝
dwm-flexipatch v.6.4.
https://github.com/bakkeby/dwm-flexipatch

Status: experimental
Last update: 26.12.2022
*/

/* Imports */
#include <X11/XF86keysym.h>

/* Appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 0;   /* 1 means swallow floating windows by default */
static const unsigned int gappih         = 15;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 15;  /* vert inner gap between windows */
static const unsigned int gappoh         = 15;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 15;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */

/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = 'A';

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "monospace:size=13" };
static const char dmenufont[]            = "monospace:size=13";

static char c000000[]                    = "#000000"; /* placeholder value */

static char normfgcolor[]                = "#c0caf5"; /* foreground (fg) */
static char normbgcolor[]                = "#1a1b26"; /* background (bg) */
static char normbordercolor[]            = "#32344a"; /* border */
static char normfloatcolor[]             = "#bb9af7"; /* border (floating) */

static char selfgcolor[]                 = "#1a1b26"; /* sel. item fg */
static char selbgcolor[]                 = "#7aa2f7"; /* sel. item bg */
static char selbordercolor[]             = "#7aa2f7"; /* sel. item border */
static char selfloatcolor[]              = "#7aa2f7"; /* sel. item (floating) */

static char titlenormfgcolor[]           = "#c0caf5"; /* title fg */
static char titlenormbgcolor[]           = "#1a1b26"; /* title bg */
static char titlenormbordercolor[]       = "#32344a"; /* title border */
static char titlenormfloatcolor[]        = "#bb9af7"; /* title (floating) */

static char titleselfgcolor[]            = "#7aa2f7"; /* sel. title fg */
static char titleselbgcolor[]            = "#1a1b26"; /* sel. title bg */
static char titleselbordercolor[]        = "#1a1b26"; /* sel. title border */
static char titleselfloatcolor[]         = "#1a1b26"; /* sel. title (floating) */

static char tagsnormfgcolor[]            = "#c0caf5"; /* tag fg */
static char tagsnormbgcolor[]            = "#1a1b26"; /* tag bg */
static char tagsnormbordercolor[]        = "#32344a"; /* tag birder */
static char tagsnormfloatcolor[]         = "#bb9af7"; /* tag (floating) */

static char tagsselfgcolor[]             = "#1a1b26"; /* sel. tag fg */
static char tagsselbgcolor[]             = "#7aa2f7"; /* sel. tag bg */
static char tagsselbordercolor[]         = "#7aa2f7"; /* sel. tag border */
static char tagsselfloatcolor[]          = "#7aa2f7"; /* sel. tag (floating) */

static char hidnormfgcolor[]             = "#1a1b26"; /* hidden fg */
static char hidselfgcolor[]              = "#1a1b26"; /* hidden sel. fg */
static char hidnormbgcolor[]             = "#414868"; /* hidden bg */
static char hidselbgcolor[]              = "#414868"; /* hidden sel. bg */
 
static char urgfgcolor[]                 = "#1a1b26"; /* urg. fg  */
static char urgbgcolor[]                 = "#7aa2f7"; /* urg. bg */
static char urgbordercolor[]             = "#f7768e"; /* urg. border */
static char urgfloatcolor[]              = "#bb9af7"; /* urg. floating */

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] =
{
	[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "Firefox", .tags = 1 << 7)
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                 drawfunc                clickfunc                hoverfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,               draw_tags,              click_tags,              hover_tags,              "tags" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,           draw_ltsymbol,          click_ltsymbol,          NULL,                    "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status,             draw_status,            click_status,            NULL,                    "status" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,           draw_wintitle,          click_wintitle,          NULL,                    "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|C|",      centeredmaster },
};

/* key definitions */
/* 
*   MOD+TAG to jump to TAG
*   MOD+CTRL+TAG to show all windows under selected TAGS
*   MOD+SHIFT+TAG to assign the TAG to a selected window
*   MOD+SHIFT+CTRL+TAG to assign a combination of 2 TAGs to a window (makes it accessible from both TAGS)
*/
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* 
*   MOD+j and MOD+k to move focus through the stack
*   MOD+s jump to previous
*   MOD+w jump to master
*   MOD+e jump to the 1st position in stack
*   MOD+a jump to the 2nd position in stack
*   MOD+z jump to the last position in stack

*   MOD+SHIFT+j and MOD+SHIFT+k to drag selected window through the stack
*   MOD+SHIFT+w puch selected window to master
*   MOD+SHIFT+e to push master to the 1st position in stack
*   MOD+SHIFT+2 to push master to the 2nd position in stack
*   MOD+SHIFT+z and MOD+SHIFT+s to push master to the last position in stack
*/
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
    { MOD, XK_s,     ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_w,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_e,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = -1 } },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
    "-i",
    "-l", "20",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
static const char *termcmd[]         = { "alacritty", NULL };
static const char *browser[]         = { "firefox", NULL };
static const char *openurl[]         = { "bookmarkd", "--open", NULL };
static const char *addurl[]          = { "bookmarkd", "--add", NULL };
static const char *brightnessup[]    = { "brightnessctl", "s", "+10%", NULL };
static const char *brightnessdown[]  = { "brightnessctl", "s", "10-%", NULL };
static const char *volumeup[]        = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *volumedown[]      = { "pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mute[]            = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *screenshot[]      = { "screenshot", NULL };
static const char *lockscreen[]      = { "slock", NULL };
static const char *kbdtoggle[]       = { "xkbd-toggle", NULL };
static const Key keys[] = {
	/* modifier                     key                        function         argument                    Comment */
    { MODKEY,                       XK_p,                      spawn,           {.v = dmenucmd } },         /* Run dmenu */
    { MODKEY|ShiftMask,             XK_Return,                 spawn,           {.v = termcmd } },          /* Open a new terminal */
	{ MODKEY|ShiftMask,             XK_c,                      killclient,      {0} },                      /* Close the window in focus */
    { MODKEY|ShiftMask,             XK_b,                      spawn,           {.v = browser } },          /* Run the browser */
    { MODKEY,                       XK_b,                      spawn,           {.v = openurl } },          /* Open a URL from bookmarks  */
    { ControlMask,                  XK_b,                      spawn,           {.v = addurl } },           /* Add highlighted text to bookmarks */
    { 0,                            XF86XK_MonBrightnessUp,    spawn,           {.v = brightnessup } },     /* Display brightness up */
    { 0,                            XF86XK_MonBrightnessDown,  spawn,           {.v = brightnessdown } },   /* Display brightness down */
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,           {.v = volumeup } },         /* Audio volume up */
    { 0,                            XF86XK_AudioLowerVolume,   spawn,           {.v = volumedown } },       /* Audio volume down */
    { 0,                            XF86XK_AudioMute,          spawn,           {.v = mute } },             /* Mute audio */
    { MODKEY,                       XK_Print,                  spawn,           {.v = screenshot } },       /* Take a screenshot */
    { MODKEY|ShiftMask,             XK_l,                      spawn,           {.v = lockscreen } },       /* Run the screenlocker */
    { MODKEY|ShiftMask,             XK_q,                      quit,            {0} },                      /* Exit to the TTY, terminates dwm */
	{ MODKEY|ControlMask|ShiftMask, XK_q,                      quit,            {1} },                      /* Restart dwm */
    { Mod1Mask|ShiftMask,           XK_b,                      togglebar,       {0} },                      /* Toggle on and off statusbar */
    { ControlMask,                  XK_space,                  spawn,           {.v = kbdtoggle } },        /* Switch keybocrd layout */
    STACKKEYS(MODKEY,                              focus)                                                   /* Focus navigation */
	STACKKEYS(MODKEY|ShiftMask,                    push)                                                    /* Push to stack control */
    { MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },                    /* Increase number of window in master */
	{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },                    /* Decrease number of windows in master */
    { MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },                  /* Decrease master width */
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },	                /* Increase master width */
    { MODKEY,                       XK_Return,     zoom,                   {0} },
    { MODKEY,                       XK_Tab,        view,                   {0} },                           /* Jump between current and previous TAGs */
    { MODKEY,                       XK_0,          view,                   {.ui = ~0 } },                   /* Display all windows from all TAGs */
    { MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },                   /* Assign all TAGs to selected window (makes it accessible from all TAGs) */
    { MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },            /* Switch to tiled layout */
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },            /* Switch to floating mode */
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },            /* Switch to monocle layout */
    { MODKEY,                       XK_c,          setlayout,              {.v = &layouts[3]} },            /* Switch to master centered layout */
    { MODKEY,                       XK_space,      setlayout,              {0} },                           /* Switch to previous layout */
    { MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },                           /* Toggle floating mode for selected window */
    { MODKEY|ShiftMask|Mod1Mask,    XK_g,          togglegaps,             {0} },                           /* Toggle on and off gaps */
    { MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },                    /* Shift focus to the previous monitor */
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },                    /* Shift focus to the next monitor */
    { MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },                    /* TO TEST */
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },                    /* TO TEST */
    TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};
