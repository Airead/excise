import traceback
import sys

from traceback_example import produce_exception


try:
    produce_exception()
except Exception as ex:
    print 'print_exception():'
    exc_type, exc_value, exc_tb = sys.exc_info()
    traceback.print_exception(exc_type, exc_value, exc_tb)
