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
    child_id = Column(Integer, ForeignKey('child.id'))
    #child = relationship("Child", backref='parents')
    #child = relationship("Child")

    def __repr__(self):
        return '<Parent %s, C %s>' % (self.id, self.child_id)


class Child(Base):
    __tablename__ = 'child'
    id = Column(Integer, primary_key=True)
    parents = relationship('Parent')

    def __repr__(self):
        return '<Child %s>' % self.id


def add_parent(uid, cid):
    p = Parent(id=uid, child_id=cid)
    session.add(p)
    session.commit()


def add_child(uid):
    c = Child(id=uid)
    session.add(c)
    session.commit()


def main():
    print 'hello manyToOne'
    print 'Parent: ', repr(Parent.__table__)
    print 'Child: ', repr(Child.__table__)

    Base.metadata.create_all(engine)

    add_child(1)
    add_child(2)
    add_parent(1, 1)
    add_parent(2, 1)

    print '---query parents---'
    query = session.query(Parent)
    parents = query.all()

    for parent in parents:
        print '====='
        print 'parent: ', parent
        #print parent.child

    print
    print '---query childs---'
    childs = session.query(Child).all()
    for c in childs:
        print '===='
        print 'child ', c
        print c.parents


if __name__ == '__main__':
    main()
