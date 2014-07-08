import pymongo

__author__ = 'airead'

items = [
    {'_id': 2},
    {'_id': 3},
    {'_id': 4},
    {'_id': 6},
]


def main():
    conn = pymongo.Connection()
    db = conn.test

    need_remove = [o['_id'] for o in items]

    db.batch.remove({'_id': {'$in': need_remove}})
    db.batch.insert(items, w=1)


if __name__ == '__main__':
    main()