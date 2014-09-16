/*  Copyright 2014 Derek Chadwick

    This file is part of the pivotal Computer Forensics Timeline Tools.

    Pivotal is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pivotal is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pivotal.  If not, see <http://www.gnu.org/licenses/>.
*/


/*
   pvcommon.h

   Title : Pivotal Computer Forensics Utilities
   Author: Derek Chadwick
   Date  : 06/07/2014

   Purpose: Pivotal global definitions.

*/


/*
   Constant Definitions
*/

#ifndef PIVOTAL_COMMON_H
#define PIVOTAL_COMMON_H

#include <stddef.h>
#include <stdio.h>

#include "uthash.h"

#define DEBUG 1

#define SERVER_PORT_STRING "59888"
#define PV_SERVER_PORT 59888
#define PV_PATH_MAX_LENGTH 4096 /* Redefine max path length since limits.h does weird things! FLTK defines this = 2048 */
#define PV_MAX_INPUT_STR 4096
#define PV_IP_ADDR_MAX 128
#define MAX_EVENT_DESC_SIZE 256
#define MAX_EVENT_ID_SIZE 8

#define PV_FILE_OUT       0x01
#define PV_SERVER_OUT     0x02
#define PV_FILTER_ON      0x04
#define PV_CAPTURE_INPUT  0x08
#define PV_UNIFIED2_INPUT 0x10
#define PV_GUI_OUT        0x20

#define PV_FILE_ACCESS_TIME   0x01
#define PV_FILE_CREATION_TIME 0x02
#define PV_FILE_MODIFY_TIME   0x04

#define DATABASE_FILE_EXT ".txt"
#define EVENT_FILE_EXT ".fle"
#define PV_SEARCH_FILTER_LIST "pv-filter-list.txt"

#ifdef LINUX_BUILD
#define PATH_SEPARATOR "/"
#define CURRENT_DIR "./"
#define CONFIG_FILE "./pivotal-linux.conf"
#define LOG_FILE "./pivotal-linux.log"
#define DATABASE_FILE "./pivotal-event-linux"
#define UNIFIED2_LOG_FILE "/var/log/snort/unified2.log"
#define EVENT_FILE "pivotal-events"
#define EVENT_LOG_PATH "./"
#else
#define PATH_SEPARATOR "\\"
#define CURRENT_DIR ".\\"
#define CONFIG_FILE ".\\pivotal.conf"
#define LOG_FILE ".\\pivotal.log"
#define DATABASE_FILE "pivotal-events"
#define EVENT_FILE "pivotal-events"

#endif /* LINUX_BUILD */

/*
   ENUMs
*/

enum error_codes { SUCCESS, FILE_ERROR, INTEGRITY_ERROR, MALLOC_ERROR, SYSTEM_ERROR, UNKNOWN_ANOMALY };
enum log_modes { LOG_ERROR, LOG_WARNING, LOG_INFO };

/*
DATA STRUCTURES
*/

struct pv_project_header
{
   char *name;
   char *investigator;
   char *summary;
   char *start_date;
   char *end_date;
   char *description;
   int event_count;
};

typedef struct pv_project_header pv_project_header_t;

struct pv_url_record
{
   char url_record_string[PV_MAX_INPUT_STR];
   double url_time;
   long access_count;
   char url_time_string[32];
   UT_hash_handle hh;
};

typedef struct pv_url_record pv_url_record_t;

struct pv_ip_record
{
   char key_value[512];
   long packet_count;
   long data_size;
   UT_hash_handle hh;
};

typedef struct pv_ip_record pv_ip_record_t;

struct pv_sensor_connection
{
   int sockfd;
   int sensor_id;
   int status;
   unsigned int event_count;
   unsigned int alert_count;
   UT_hash_handle hh;
};

typedef struct pv_sensor_connection pv_sensor_connection_t;

/* pvutil.c */

int fatal(char *str);
void *xcalloc (size_t size);
void *xmalloc (size_t size);
void *xrealloc (void *ptr, size_t size);
int xfree(char *buf, int len);
int print_help();
char* xitoa(int value, char* result, int len, int base);
int get_time_string(char *tstr, int slen);
int get_ip_address(char *interface, char *ip_addr);
int validate_ipv4_address(char *ipv4_addr);
int validate_ipv6_address(char *ipv6_addr);
char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);

/* pvsocket.c */

int init_client_socket(char *server_ip_address);
int init_server_socket(int port_number, void *(* connector)(void *));
int send_event(int sockfd, char *event_string);
char *get_response(int sockfd, char *in_buffer);
int close_socket(int sockfd);
void *connection_handler(void *socket_desc);

/* pvlog.c */

int open_log_file(char *startup_path);
int print_log_entry(char *estr);
int sprint_log_entry(char *estr, char *eval);
int iprint_log_entry(char *estr, int ival);
int close_log_file();

/* pveventfile.c */

FILE *open_fineline_event_file(char *evt_file_name);
int write_fineline_event_record(char *estr);
int write_fineline_project_header(char *pstr);
int close_fineline_event_file();
int dump_statistics();
int write_event_record(char *event_string);
int create_event_record(char *event_string, char *data_string);

/* pveventlog.c */

FILE *open_sensor_log_file(char *evt_file_name);
int write_sensor_log_record(FILE *evt_file, char *estr);
int write_project_header(FILE *evt_file, char *pstr);
int close_sensor_log_file(FILE* evt_file);

/* pvipmap.c */

void add_ip(pv_ip_record_t *flip);
pv_ip_record_t *find_ip(char *lookup_string);
void write_ip_map(FILE *outfile);
void send_ip_map(int sock_desc);
void print_ip_map();
void delete_ip(pv_ip_record_t *ip_record);
void delete_all_ips();
pv_ip_record_t *get_first_ip_record();
pv_ip_record_t *get_last_ip_record();




#endif

