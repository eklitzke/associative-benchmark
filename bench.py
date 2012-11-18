import optparse
import os
import struct
import time

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('-n', '--num', type='int', default=1000000,
                      help='Number of pairs to use')
    parser.add_option('-s', '--string', default=False, action='store_true',
                      help='Use strings intead of integers')

    opts, args = parser.parse_args()

    type_name = "string" if opts.string else "integer"
    t0 = time.time()
    print 'generating list with %d %s pairs...' % (opts.num, type_name)
    vals = []
    if opts.string:
        for x in xrange(opts.num):
            vals.append((os.urandom(8), os.urandom(8)))
    else:
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
