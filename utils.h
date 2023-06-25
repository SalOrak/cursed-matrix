#ifndef __UTILS_H
#define __UTILS_H

#define LOG(message) if(LOG_FLAG) __write_log(LOG_FILE,message);
void __write_log(char * filename, char * text);

#endif // __UTILS_H
