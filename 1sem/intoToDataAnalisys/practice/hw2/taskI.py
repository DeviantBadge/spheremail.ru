import copy


class FragileDict:
    _data = {}
    _lock = None

    def __init__(self, _data={}):
        self._data = copy.deepcopy(_data)
        self._lock = True

    def __getitem__(self, key):
        return self._data[key]

    def __setitem__(self, key, value):
        if not self._lock:
            self._data[key] = value
            return value
        else:
            raise RuntimeError("Protected state")

    def __contains__(self, item):
        return item in self._data

    def __enter__(self):
        self._lock = False
        self._backup = self._data
        self._data = copy.deepcopy(self._data)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        if exc_val is not None:
            print("Exception has been suppressed.")
            self._data = self._backup
        else:
            self._data = copy.deepcopy(self._data)
        self._lock = True
        delattr(self, "_backup")
        return self


if __name__ == '__main__':
    d = FragileDict({'key': 5})

    with d:
        d['key'] = 6
        print(d['key'])
        d.a = 10
        d['ord'] = 7
        print('ord' in d and d['ord'] == 7)
        raise Exception()

    print(d['key'])
    print(d.__dict__)
    print('ord' not in d)