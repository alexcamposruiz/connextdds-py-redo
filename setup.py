from setuptools import setup
from configparser import ConfigParser

def read_config():
    config = ConfigParser()
    config.read('package.cfg')
    return config

def get_setup_params():
    config = read_config()
    parameters = {}
    platform = config.get('package', 'platform')
    libraries = config.get('package', 'libraries-rti')
    nddshome = config.get('package', 'nddshome')
    parameters['description'] = f'Connext Add-ons for {platform}. Includes the following libraries: {libraries} - obtained from {nddshome}'
    version = config.get('package', 'version', fallback='0.0.1')
    if version:
        parameters['version'] = version

    return parameters

# Creates a wheel that contains add-on native libraries as part of the "rti"
# package so that when it is installed it adds them to a previous installation
# of rti.connext. This allows using add-on libraries in a Connext Python
# without having to configure environment variables.
params = get_setup_params()
setup(
    package_data={"rti": ["*"]},
    **params
)
