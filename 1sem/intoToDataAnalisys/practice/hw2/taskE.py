import functools


def once(func):
    once.__calls__ = getattr(once, "__calls__", {})

    @functools.wraps(func)
    def wrapper(*args, **argv):
        once.__calls__[func.__name__] = once.__calls__.get(func.__name__, None) or {'result' : func(*args, **argv)}
        return once.__calls__[func.__name__]['result']

    return wrapper


@once
def bonjour():
    print("Bonjour le monde!")


if __name__ == "__main__":
    bonjour()
    bonjour()
    bonjour()