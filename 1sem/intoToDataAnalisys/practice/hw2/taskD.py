import functools
import time


def stopwatch(func):
    @functools.wraps(func)
    def wrapper(*args, **argv):
        start = time.time()
        print("`%s` started" % func.__name__)
        result = func(*args, **argv)
        print("`%s` finished in %.2fs" % (func.__name__, time.time() - start))
        return result
    return wrapper
