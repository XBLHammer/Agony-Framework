/* Menu Dimensions */
float flOptionH = 20.0f;
float flOptionW = 150.0f;
float flMenuW = 600.0f;
float flBSize = 6.0f;
float flHSize = 16.0f;

/* Menu Location */
float flMenuX = 250.0f;
float flMenuY = 50.0f;

/* Misc */
char *szHeaderFont = "fonts/hudbigfont";
char *szOptionFont = "fonts/hudbigfont";
float flHeaderSize = 0.32;
float flOptionSize = 0.32;
const char *szIniPath = "HDD:\\TamperedCE.ini";

void playerSub(int c) {
	MenuVars.currentMenu = c + 7;
}