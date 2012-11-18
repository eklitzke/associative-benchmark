import optparse
import os
import struct
import time

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('-n', '--num', type='int', default=1000000,
                      help='Number of integers to use')
    opts, args = parser.parse_args()

    t0 = time.time()
    print 'generating number list with %d integer pairs...' % (opts.num,)
    vals = []
    for x in xrange(opts.num):
        vals.append(struct.unpack('ii', os.urandom(8)))
    print 'generated in %d ms' % ((time.time() - t0) * 1000,)

    print '\ndict\n---------'
    d = {}
    t0 = time.time()
    for k, v in vals:
        d[k] = v
    print 'create: %d' % ((time.time() - t0) * 1000,)

    t0 = time.time()
    for k, v in vals:
        d[k]
    print 'search: %d' % ((time.time() - t0) * 1000,)
