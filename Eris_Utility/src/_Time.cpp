#include "Eris_Utility/_Time.h"


_Time _Time::s_file = _Time("%Y-%m-%d_%H-%M-%S");
_Time _Time::s_programStartTime = _Time("%Y-%m-%d_%H-%M-%S");
_Time _Time::s_datetime = _Time();
_Time _Time::s_date = _Time("%d %b %Y");
_Time _Time::s_time = _Time("%H:%M:%S");
