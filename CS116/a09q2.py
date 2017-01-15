##
## ***************************************************
## Lucus Esson (20615533)
## CS 116 Winter 2016
## Assignment 9, Problem 2
## ***************************************************
##

import check

class Time:
    '''Fields: hours, minutes, seconds'''
#    requires:
#   0 <= hours <= 23
#   0 <= minutes <= 59
#   0 <= seconds <= 59
    def __init__(self, hour, minute, second):
        self.hours = hour
        self.minutes = minute
        self.seconds = second   

    def __repr__(self):
        return "{0.hours}:{0.minutes}:{0.seconds}".format(self)

    def __eq__(self, other):
        return self.hours == other.hours and \
            self.minutes == other.minutes and \
            self.seconds == other.seconds

# find_early(events) consumes a list of Time objects, and produces the earliest
#   Time object in the list, events. 
# find_early: (listof Time) -> Time

def find_early(events):
    x = Time(23,59,59)
    for t in events:
        total_t = (t.hours * 60) + t.minutes + (t.seconds / 100)
        total_x = (x.hours * 60) + x.minutes + (x.seconds / 100)
        if total_t <= total_x:
            x = events[0]
            events = events[1:]
    return x


# next_event(now, event) consumes a Time object called now, and a list of
#   Time objects called events, and produces a Time object representing
#   the next event that will occur given the current time is now.
# next_event: Time (listof Time) -> Time
# Requires: If events is empty, None is produced
# Examples:
# next_event(Time(17,23,10), [Time(15,45,0), Time(6,30,0), Time(22,0,0)])
#           => Time(22,0,0)

# next_event(Time(0,0,0), []) => None

def next_event(now, events):
    if events == []:
        return None
    start = events
    x = Time(23,59,59)
    y = (now.hours * 60) + now.minutes + (now.seconds / 100)
    for t in events:
        total_t = (t.hours * 60) + t.minutes + (t.seconds / 100)
        total_x = (x.hours * 60) + x.minutes + (x.seconds / 100)
        if y <= total_t and total_t <= total_x:
            x = events[0]
            events = events[1:]
        else:
            events = events[1:]
    if x == Time(23,59,59):
        return find_early(start)
    else:
        return x

# Test 1:
check.expect("Q2T1", next_event(Time(17,23,10), [Time(15,45,0), Time(6,30,0), Time(22,0,0)]), Time(22,0,0))

# Test 2:
check.expect("Q2T2", next_event(Time(22,0,10),[Time(15,45,0), Time(6,30,0), Time(22,0,0)]), Time(6,30,0))

# Test 3:
check.expect("Q2T3", next_event(Time(15,45,0), [Time(15,45,0), Time(6,30,0), Time(22,0,0)]), Time(15,45,0))

# Test 4:
check.expect("Q2T4", next_event(Time(0,45,0), [Time(1,45,0), Time(6,30,0), Time(22,0,0)]), Time(1,45,0))

# Test 5:
check.expect("Q2T5", next_event(Time(23,45,0), [Time(1,45,0), Time(6,30,0), Time(23,50,0)]), Time(23,50,0))

# Test 6:
check.expect("Q2T6", next_event(Time(23,45,0), []), None)

        