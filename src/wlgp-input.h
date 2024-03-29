#ifndef MY_HEADER_FILE_H
#define MY_HEADER_FILE_H
#define START 1
#define STOP 0

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <linux/uinput.h>
#include <stdint.h>

#include <libevdev.h>
#include <libevdev-util.h>
#include <libevdev-int.h>
#include <event-names.h>

struct mt_status {
    int pressed;
    int released;
    int max_slots;
    int x[10],y[10];
    int id[10];
    int numTouches;
    int touch_end;
};

struct td {
int x;
int y;
int id;
int prs;
};

struct wlkb_in {
    struct pollfd fds[1];
    struct uinput_setup usetup;
    struct input_absinfo abs_x, abs_y;
    struct input_event ev;
    struct libevdev *dev;
    struct mt_status mt;
    fd_set rfds;
    int fd,tp_fd;
    int timeout;
    bool tp_on;
    char device_name[25],conf_name[25],img_name[25];
};

int print_event(struct wlkb_in *data);
int check_ev(struct input_event *ie, uint16_t type, uint16_t code, int val);
void init(char *device,struct wlkb_in *data);
int dt_press(struct wlkb_in *data,bool *press);
char *getdevicename();
void getdeviceresolution(struct  wlkb_in *data);
int get_event(struct  wlkb_in *data,int timeout);
void touchstatus(struct wlkb_in *data);
struct td dt_touch_area(struct wlkb_in *data,int x,int y,int length_x,int length_y);
void dt_touch_pad(struct wlkb_in *data,int press,int x,int y,int tlx,int tly);
void emit(int fd, uint16_t type, uint16_t code, int val);
int syn(struct wlkb_in *data);
void send_event(int fd, uint16_t type, uint16_t code,int val);
void close_fd(struct wlkb_in *data);
#endif
