from functools import wraps, update_wrapper
import click


# @click.group(chain=True, invoke_without_command=True)
@click.group(chain=True)
@click.option('-i', '--input', type=click.File('r'))
def cli(input):
    pass


@cli.resultcallback()
def process_pipeline(processors, input):
    print processors
    print input
    for processor in processors:
        print processor.__name__


@cli.command('uppercase')
def make_uppercase():
    def aaa():
        pass
    def processor():
        pass
    return update_wrapper(processor, aaa)

@cli.command('lowercase')
def make_lowercase():
    return 'lowercase'

if __name__ == '__main__':
    cli()
