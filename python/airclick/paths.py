import click


@click.command()
@click.option('paths', '--paths', envvar='PATH', multiple=True, type=click.Path())
def cli(paths):
    for path in paths:
        click.echo(path)

if __name__ == '__main__':
    cli()
