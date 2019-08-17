#include <lilly_os.h>
#include <system.hpp>
#include <sysutils.hpp>


void lilly_os_get_current_time_stamp(const p_date_time time_stamp)
{
  TDateTime date = TDateTime::CurrentDateTime();
  uint16 year,month,day,hour,minute,second,msecond;



	DecodeTime(date,hour,minute,second,msecond);

	DecodeDate(date,year,month,day);

	time_stamp->hours = hour;
	time_stamp->minutes = minute;
	time_stamp->seconds = second;
	time_stamp->day = day;
	time_stamp->month = month;
	time_stamp->year = year;
	time_stamp->reserved = msecond;

    return;

}
