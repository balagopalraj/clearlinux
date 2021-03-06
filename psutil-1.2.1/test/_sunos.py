#!/usr/bin/env python

# Copyright (c) 2009, Giampaolo Rodola'. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Sun OS specific tests.  These are implicitly run by test_psutil.py."""

import datetime

import psutil
from test_psutil import *


class SunOSSpecificTestCase(unittest.TestCase):

    def test_swap_memory(self):
        out = sh('swap -l -k')
        lines = out.strip().split('\n')[1:]
        if not lines:
            raise ValueError('no swap device(s) configured')
        total = free = 0
        for line in lines:
            line = line.split()
            t, f = line[-2:]
            t = t.replace('K', '')
            f = f.replace('K', '')
            total += int(int(t) * 1024)
            free += int(int(f) * 1024)
        used = total - free

        psutil_swap = psutil.swap_memory()
        self.assertEqual(psutil_swap.total, total)
        self.assertEqual(psutil_swap.used, used)
        self.assertEqual(psutil_swap.free, free)

    def test_BOOT_TIME(self):
        psutil_bt = datetime.datetime.fromtimestamp(psutil.BOOT_TIME).strftime(
            "%b %d %H:%M")
        sys_bt = sh('last reboot | head -1')
        sys_bt = ' '.join(sys_bt.split()[-3:])
        self.assertEqual(sys_bt, psutil_bt)


def test_main():
    test_suite = unittest.TestSuite()
    test_suite.addTest(unittest.makeSuite(SunOSSpecificTestCase))
    result = unittest.TextTestRunner(verbosity=2).run(test_suite)
    return result.wasSuccessful()

if __name__ == '__main__':
    if not test_main():
        sys.exit(1)
