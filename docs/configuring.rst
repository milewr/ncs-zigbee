.. _ug_zigbee_configuring:

Configuring |addon|
###################

.. contents::
   :local:
   :depth: 2

This page describes what is needed to start working with Zigbee using the |addon| for the |NCS|.
|kconfig_search|

.. _zigbee_ug_libs:

Required libraries and drivers
******************************

Zigbee requires the following modules:

* :ref:`zigbee_zboss`, with the :ref:`lib_zigbee_osif` subsystem acting as the linking layer between the ZBOSS stack and the |NCS|.
  The ZBOSS library is enabled by the ``CONFIG_ZIGBEE_ADD_ON`` Kconfig option.
  For more information about the ZBOSS stack, see also the `external ZBOSS development guide and API documentation`_.
* `IEEE 802.15.4`_ radio driver - This library is automatically enabled when working with Zigbee on Nordic Semiconductor's development kits.

.. _zigbee_ug_configuration:

Mandatory configuration
***********************

To use the Zigbee protocol, set the ``CONFIG_ZIGBEE_ADD_ON`` Kconfig option.
Setting this option enables all the peripherals required for the correct operation of the Zigbee protocol and allows you to use them.

After that, you have to define the Zigbee device role for the Zigbee application or sample by setting one of the following Kconfig options:

* Router role: ``CONFIG_ZIGBEE_ROLE_ROUTER``
* End Device role: ``CONFIG_ZIGBEE_ROLE_END_DEVICE``
* Coordinator role: ``CONFIG_ZIGBEE_ROLE_COORDINATOR``

Setting any of these options enables the respective ZBOSS role library.
This is needed because End Devices use different libraries than Routers and Coordinators.

For instructions about how to set Kconfig options, see `Configuring and building`_ in the |NCS| documentation.

.. _zigbee_ug_sed:

Sleepy End Device behavior
==========================

The Sleepy End Device (SED) behavior is a Zigbee stack feature that enables the sleepy behavior for the end device.

By default, the end device regularly polls its parent for data.
When the SED behavior is enabled and no frames are available for reception after the last poll, the SED disables its radio until the next scheduled poll.
The Zigbee stack's own scheduler informs the application about periods of time when nothing is scheduled for any of the device roles.
This allows the stack to enter the sleep state during these periods, which also powers off some peripherals for the SED.

When the Zigbee stack thread goes to sleep, the Zigbee thread can enter the suspend state for the same amount of time as the stack's sleep.
The thread will be automatically resumed after the sleep period is over or on an event.

For this feature to work, make sure to call the :c:func:`zb_set_rx_on_when_idle` ZBOSS API with the ``ZB_FALSE`` parameter before starting the ZBOSS stack.
This function specifies whether the device should have the radio disabled between the polls to parent.
This feature does not require enabling any additional options in Kconfig.

In the :ref:`Zigbee light switch sample <zigbee_light_switch_sample>` in the |NCS|, after you enable the SED behavior extension, the sleepy behavior can be triggered by pressing a predefined button when the device is booting.
This action results in calling the ZBOSS API that activates this feature.

Power saving during sleep
-------------------------

With the sleepy behavior enabled, the unused part of RAM memory is powered off, which allows to lower the power consumption even more.
The sleep current of MCU can be lowered by completing the following steps:

1. Turn off UART by setting the ``CONFIG_SERIAL`` Kconfig option to ``n``.
#. Enable the ``CONFIG_RAM_POWER_DOWN_LIBRARY`` Kconfig option.

Optional configuration
**********************

After enabling the Zigbee protocol and defining the Zigbee device role, you can enable additional options in Kconfig and modify `ZBOSS stack start options`_.

Device operational channel
==========================

You can enable one of the following alternative options to select the channel on which the Zigbee device can operate:

  * ``CONFIG_ZIGBEE_CHANNEL_SELECTION_MODE_SINGLE`` - Single mode is enabled by default.
    The default channel is set to 16.
    To set a different channel, edit the ``CONFIG_ZIGBEE_CHANNEL`` Kconfig option to the desired value.
  * ``CONFIG_ZIGBEE_CHANNEL_SELECTION_MODE_MULTI`` - In this mode, you get all the channels enabled by default.
    To configure a custom set of channels in the range from 11 to 26, edit the ``CONFIG_ZIGBEE_CHANNEL_MASK`` Kconfig option.
    For example, you can set channels 13, 16, and 21.
    You must have at least one channel enabled with this option.

.. _ug_zigbee_configuring_eui64:

IEEE 802.15.4 EUI-64 configuration
==================================

The Zigbee stack uses the EUI-64 address that is configured in the IEEE 802.15.4 shim layer.
By default, it uses an address from Nordic Semiconductor's pool.

If your devices should use a different address, you can change the address according to your company's addressing scheme.

.. include:: includes/ieee802154_eui64_conf_nrf54l.txt

At the end of the configuration process, you can check the EUI-64 value using :ref:`lib_zigbee_shell`:

.. code-block:: console

   > zdo eui64
   8877665544332211
   Done

.. note::
    Alternatively, you may use the Production Configuration feature to change the address.
    The Production Configuration takes precedence over the shim's configuration.

ZBOSS stack start options
=========================

Zigbee is initialized after Zephyr's kernel start.
The ZBOSS stack can be started using one of the following options:

* Started and executed from the main thread, as `described in the ZBOSS development guide <Stack commissioning start sequence_>`_.
* Started from a dedicated Zephyr thread, which in turn can be created and started by calling :c:func:`zigbee_enable`.

The dedicated thread can be configured using the following Kconfig options:

* ``CONFIG_ZBOSS_DEFAULT_THREAD_PRIORITY`` - Defines thread priority; set to ``3`` by default.
* ``CONFIG_ZBOSS_DEFAULT_THREAD_STACK_SIZE`` - Defines the size of the thread stack; set to ``2048`` by default.

.. _zigbee_ug_logging:

Custom logging per module
=========================

Logging is handled with the ``CONFIG_LOG`` Kconfig option.
This option enables logging for both the stack and Zephyr's `Logging`_ API.

.. _zigbee_ug_logging_application_logs:

Default Zigbee application logging
----------------------------------

The Zigbee application uses the ``INF`` logging level by default.
This level can be changed only by modifying the sample code.

.. _zigbee_ug_logging_stack_logs:

Stack logs
----------

The stack logs are independent from Zephyr's `Logging`_ API.
To customize them, use the following Kconfig options:

* ``CONFIG_ZBOSS_ERROR_PRINT_TO_LOG`` - Allows the application to log ZBOSS error names; enabled by default.
* ``CONFIG_ZBOSS_TRACE_MASK`` - Sets the modules from which ZBOSS will log the debug messages with ``CONFIG_ZBOSS_TRACE_LOG_LEVEL``; no module is set by default.
* ``CONFIG_ZBOSS_TRAF_DUMP`` - Enables logging of the received 802.15.4 frames over ZBOSS trace log if ``CONFIG_ZBOSS_TRACE_LOG_LEVEL`` is set; disabled by default.

The stack logs are provided in a binary format.
You can configure how they are printed with the following Kconfig options:

* ``CONFIG_ZBOSS_TRACE_HEXDUMP_LOGGING`` - Stack logs are printed as hexdump using Zephyr's `Logging`_ API.
  This option is enabled by default.
* ``CONFIG_ZBOSS_TRACE_BINARY_LOGGING`` - Stack logs are printed in the binary format using one of the following independent serial backends of your choice:

  * ``CONFIG_ZBOSS_TRACE_UART_LOGGING`` - UART serial.
    This backend is enabled by default.

  To specify the serial device, you need to set the ``ncs,zboss-trace-uart`` choice in devicetree like this:

  .. code-block:: devicetree

     chosen {
         ncs,zboss-trace-uart = &uart1;
     };

..
  * ``CONFIG_ZBOSS_TRACE_BINARY_NCP_TRANSPORT_LOGGING`` - Stack logs are printed in the binary format using the NCP transport channel.

Stack logs are stored in the internal buffer if they are printed using Zephyr's `Logging`_ API or the independent serial backend.
You can customize the buffer size with the ``CONFIG_ZBOSS_TRACE_LOGGER_BUFFER_SIZE`` Kconfig option.
The buffer size must be larger than ``256`` and smaller than ``2147483648``

..
  If NCP transport channel is used, stack logs are stored in the buffer used for NCP transport.
  This buffer's size can be configured with the ``CONFIG_ZIGBEE_UART_TX_BUF_LEN`` Kconfig option.

.. _zigbee_ug_logging_logger_options:

Zephyr's logger options
-----------------------

You can configure custom logger options for each Zigbee and ZBOSS module.
To do this, configure the related Kconfig option for one or more modules:

* ``CONFIG_ZBOSS_TRACE_LOG_LEVEL``
* ``CONFIG_ZBOSS_OSIF_LOG_LEVEL``
* ``CONFIG_ZIGBEE_SHELL_LOG_LEVEL``
* ``CONFIG_ZIGBEE_APP_UTILS_LOG_LEVEL_CHOICE``
* ``CONFIG_ZIGBEE_LOGGER_EP_LOG_LEVEL_CHOICE``
* ``CONFIG_ZIGBEE_SCENES_LOG_LEVEL``

For each of the modules, you can set the following logging options:

* ``LOG_LEVEL_OFF`` - Turns off logging for this module.
* ``LOG_LEVEL_ERR`` - Enables logging only for errors.
* ``LOG_LEVEL_WRN`` - Enables logging for errors and warnings.
* ``LOG_LEVEL_INF`` - Enables logging for informational messages, errors, and warnings.
* ``LOG_LEVEL_DBG`` - Enables logging for debug messages, informational messages, errors, and warnings.

For example, setting ``CONFIG_ZBOSS_TRACE_LOG_LEVEL_INF`` will enable logging of informational messages, errors, and warnings for the ZBOSS Trace module.

Reduced power consumption
=========================

You can reduce the amount of power used by your device by enabling the `RAM power-down`_ library.
This library is also used for `Power saving during sleep`_.


.. _zigbee_ug_static_partition:

Upgrading Zigbee application
****************************

When upgrading the Zigbee application, use the `Static and dynamic configuration`_ of the Partition Manager to ensure that ZBOSS' NVRAM is placed in the same area of flash.
This is because enabling additional features (for example, Zephyr's `Non-Volatile Storage (NVS)`_) can change the placement of the partition in the flash and the ZBOSS settings can be lost, as the application is not able to find the partition.

The static configuration is required regardless of the application version and the upgrading method (:ref:`lib_zigbee_fota` or `Secure bootloader chain`).
