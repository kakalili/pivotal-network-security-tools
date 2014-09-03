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
   pivot_sensor.h

   Title : Pivotal Computer Forensics Utilities
   Author: Derek Chadwick
   Date  : 06/07/2014

   Purpose: Pivotal global definitions.

*/


/*
   Constant Definitions
*/

#ifndef PIVOTAL_SENSOR_H
#define PIVOTAL_SENSOR_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <ifaddrs.h>
#include <pcap.h>


/* pivot-sensor.c */

int parse_command_line_args(int argc, char *argv[], char *capture_device, char *pv_event_filename, char *server_ip_address, char *filter_file);
int show_sensor_help();

/* pvsniffer.c */

pcap_t* open_pcap_socket(char* device, const char* bpfstr);
void capture_loop(int packets, pcap_handler func);
void parse_packet(u_char *user, struct pcap_pkthdr *packethdr, u_char *packetptr);
void process_packet(u_char *user, struct pcap_pkthdr *packethdr, u_char *packetptr);
void terminate_capture(int signal_number);
int start_capture(char *interface, const char *bpf_string, char *event_file, char *server_address, int mode);

/* pvfilter.c */

int load_bpf_filters(char *filter_filename, char *filter_string);

/* pvurlmap.c */

void add_url(pv_url_record_t *flurl);
pv_url_record_t *find_url(char *lookup_string);
void write_url_map(FILE *outfile);
void send_url_map();
void delete_url(pv_url_record_t *url_record);
void delete_all_urls();
pv_url_record_t *get_first_url_record();
pv_url_record_t *get_last_url_record();

/* pvipmap.c */

void add_ip(pv_ip_record_t *flip);
pv_ip_record_t *find_ip(char *lookup_string);
void write_ip_map(FILE *outfile);
void send_ip_map();
void print_ip_map();
void delete_ip(pv_ip_record_t *ip_record);
void delete_all_ips();
pv_ip_record_t *get_first_ip_record();
pv_ip_record_t *get_last_ip_record();

/* pvtail.c */

int open_tail_pipe(char *log_file_name);
int start_tail(int pivot_options, int log_option);
int follow_tail();

/* pveventfile.c */

FILE *open_fineline_event_file(char *evt_file_name);
int write_fineline_event_record(char *estr);
int write_fineline_project_header(char *pstr);
int close_fineline_event_file();
int dump_statistics();




#endif
