APPNAME = 'yut'
VERSION = '20101106'

top = '.'
out = 'build'


def options(opt):
    opt.tool_options('compiler_cxx')
    opt.tool_options('boost')


def configure(conf):
    conf.check_tool('compiler_cxx')
    conf.check_tool('boost')

    conf.env.CCFLAGS  = ['-g', '-O0', '-Wall']
    conf.env.CXXFLAGS = ['-g', '-O0', '-Wall']

    # Boost
    conf.check_boost(lib='unit_test_framework', mandatory=True)


def build(bld):
    bld.recurse('test')
