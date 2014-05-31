from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, ForeignKey
from sqlalchemy.orm import relationship, sessionmaker

__author__ = 'airead'

engine = create_engine('sqlite:///:memory:', echo=True)

Session = sessionmaker(bind=engine)
session = Session()


Base = declarative_base()


class Parent(Base):
    __tablename__ = 'parent'
    id = Column(Integer, primary_key=True)
    children = relationship("Child", uselist=False)

    def __repr__(self):
        return '<Parent %s>' % self.id


class Child(Base):
    __tablename__ = 'child'
    id = Column(Integer, primary_key=True)
    parent_id = Column(Integer, ForeignKey('parent.id'))

    def __repr__(self):
        return '<Child %s, P %s>' % (self.id, self.parent_id)


def add_parent(uid):
    p = Parent(id=uid)
    session.add(p)
    session.commit()


def add_child(uid, pid):
    c = Child(id=uid, parent_id=pid)
    session.add(c)
    session.commit()


def main():
    print 'hello oneToMany'
    print 'Parent: ', repr(Parent.__table__)
    print 'Child: ', repr(Child.__table__)

    Base.metadata.create_all(engine)

    add_parent(1)
    add_parent(2)
    add_child(1, 1)
    add_child(2, 1)

    print '---query parents---'
    query = session.query(Parent)
    parents = query.all()

    for parent in parents:
        print '====='
        print 'parent: ', parent.id
        print parent.children

    print
    print '---query childs---'
    childs = session.query(Child).all()
    print childs


if __name__ == '__main__':
    main()
