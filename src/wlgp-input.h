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
    int numTouches;
};


struct wlkb_in {
    struct pollfd fds[1];
    struct uinput_setup usetup;
    struct input_absinfo abs_x, abs_y;
    struct input_event ev;
    struct libevdev *dev;
    struct mt_status mt;
    int fd;
};

void init(char *device,struct wlkb_in *data);
void getdeviceresolution(struct  wlkb_in *data);
void touchstatus(struct wlkb_in *data);
void emit(int fd, uint16_t type, uint16_t code, int val);
void send_event(int fd, uint16_t type, uint16_t code,int val);
#endif
