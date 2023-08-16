<br />
<p align="center">
  <a href="https://github.com/rticommunity/connextdds-py">
    <img src="docs/source/_static/rti-logo-tag-StackedRight.png" alt="RTI Connext Python API" height="50">
  </a>
</p>


<p align="center"><h1 align="center"><strong>RTI Connext Python API</strong></h1></p>

<p align="center">
  <br />
  <a href="https://community.rti.com/static/documentation/connext-dds/current/doc/manuals/connext_dds_professional/getting_started_guide/index.html">Getting Started</a>
  ·
  <a href="https://community.rti.com/static/documentation/connext-dds/current/doc/api/connext_dds/api_python/overview.html">API Overview</a>
  ·
  <a href="https://community.rti.com/static/documentation/connext-dds/current/doc/api/connext_dds/api_python/quick.html">API Reference</a>
  ·
  <a href="https://community.rti.com/static/documentation/connext-dds/current/doc/api/connext_dds/api_python/examples.html">Examples</a>
</p>

<br>

## Installing the Connext Python API

The [Connext Getting Started Guide](https://community.rti.com/static/documentation/connext-dds/current/doc/manuals/connext_dds_professional/getting_started_guide/index.html)
helps you install the software and run your first RTI Connext Python application while learning general concepts of Connext.

Note: starting with Connext 7.2.0, the Connext Python API is **no longer
distributed as buildable source**. This repository now contains a utility script
that helps install add-on libraries using `pip`.

## Installing Connext Add-On Libraries

The Connext Python API can load Connext add-on libraries that provide additional
capabilities such as monitoring, security, transports.

You can add add-on libraries to the rti.connext package in your Python
installation or virtual environment. Your Connext Python applications will be
able to use these add-ons without having to configure the path to the libraries
at runtime.

To install add-on libraries in your rti.connext python package follow these steps:

* Install a Connext Host and Target packages and any additional add-on Connext
packages as explained in the Getting Started Guide. Let's call the installation
directory `<install_dir>`.

* Clone this repository, open a shell and cd into the repository directory.

* Run the following script to select which add-ons you want to include in the
Python wheel:

```sh
python configure.py [add-ons] -n <install_dir> <architecture>
```

For example:

```sh
python configure.py --tcp --monitoring -n /opt/rti_connext_dds-7.2.0 x64Linux3gcc5.4.0
```

* Create the wheel file that includes those add-on libraries:

```sh
python setup.py bdist_wheel
```

This creates a wheel file for a package called "rti.addons".

* Install the wheel file:

```sh
pip install dist/*.whl
```


You can see which libraries you installed by running:

```sh
pip show rti.addons
```

To uninstall the add-on libraries, run:

```sh
pip uninstall rti.addons
```


