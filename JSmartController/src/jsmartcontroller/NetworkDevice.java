/*
 * Copyright 2016 Ollie Bown
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package jsmartcontroller;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.InterfaceAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Scanner;

public abstract class NetworkDevice {

/**
 * This code has been taken from HappyBrackets
 */
//
//		//ensure we have a local suffix
    /**
     * Decide if a network interface is useful for HappyBrackets
     * @param ni networkInterface
     * @return boolean
     */
	public static boolean isViableNetworkInterface(NetworkInterface ni) {
		try {
			if ( !ni.supportsMulticast()												) return false;
			//if ( ni.isLoopback()														) return false;
            if ( !ni.isLoopback() && !isValidMac(selectMAC(ni))                         ) return false;
			if ( !ni.isUp()										  						) return false;
			if ( ni.isVirtual()															) return false; // No sub interfaces
			//if ( ni.getDisplayName().matches(".*[Vv]irtual.*")	                    ) return false; //try and catch out any interfaces which belong to a virtualisation environment
            if ( !ni.getInetAddresses().hasMoreElements()                               ) return false; // Make sure we can access at least one address for this interface.
		} catch (SocketException e) {
            System.out.println("Error checking interface {}" + ni.getName() + e.getMessage());
			return false;
		}
		return true;
	}

    /**
     * Obtain a list of NetworkInterface objects which are of interest to HappyBrackets.
     * @return a List of Viable network Interfaces
     */
	public static ArrayList<NetworkInterface> viableInterfaces() {
        ArrayList<NetworkInterface> viableInterfaces = new ArrayList<>();

        try {
            for (Enumeration<NetworkInterface> i = NetworkInterface.getNetworkInterfaces(); i.hasMoreElements();) {
                NetworkInterface netInt = i.nextElement();
                // Windows by default has a lot of sub interfaces, so we need to filter these out
                if (isViableNetworkInterface(netInt)) {
                    viableInterfaces.add(netInt);

                }
                else {
                    //logger.debug("    {} ({}) : IGNORED", netInt.getName(), netInt.getDisplayName());
                }
            }
        } catch (SocketException e) {
            System.out.println("Unable to collect network interfaces! " + e.getMessage());
        }

        return viableInterfaces;
    }

    /**
     * Decide on what my hostname should be.
     * @param ni network Interface
     * @return host name as String
     */
    public static String selectHostname(NetworkInterface ni) {
        return removeLinkLocalSuffix(ni.getInetAddresses().nextElement().getCanonicalHostName());
    }

    /**
     * Decide what my IP address should be.
     * @param ni network interface
     * @return IP address as String
     */
    public static String selectIP(NetworkInterface ni) {
        return removeLinkLocalSuffix(ni.getInetAddresses().nextElement().getHostAddress());
    }

    /**
     * * Remove the trailing link local from IPv6 address and allow IPv4 to pass through.
     * @param address The input address
     * @return the IPv4 address
     */
    public static String removeLinkLocalSuffix(String address) {
        return address.split("%")[0];
    }

    /**
     * Decide what my MAC address should be
     * @param ni Network Interface
     * @return MAC address as String
     */
    public static String selectMAC(NetworkInterface ni) {
        try {
            byte[] mac = ni.getHardwareAddress();
            if (mac == null) {
                mac = new byte[] {0, 0, 0, 0, 0, 0};
            }

            StringBuilder builder = new StringBuilder();
            for (byte a : mac) {
                builder.append(String.format("%02x", a));
            }

            return builder.substring(0, builder.length());
        }
        catch (SocketException e) {
            System.out.println("Unable to obtain MAC address for interface {}" +  ni.getDisplayName() + e.getMessage());
            return "error";
        }
    }

    public static boolean isValidMac(String mac) {
        if (mac.equals(emptyMac())) {
            return false;
        }
        return true;
    }

    public static String emptyMac() {
        return "000000000000";
    }

    public static String getDeviceName() {
        if (System.getProperty("os.name").contains("Windows")) {
            return "WindowsDevice";
        }
        try {
            Scanner s = new Scanner(new File("/etc/hostname"));
            String line = s.next();
            if (line != null && !line.isEmpty() && !line.endsWith("-")) {
                System.out.println("Read device name from /etc/hostname. Name is {} + line");
                return line;
            }
            s.close();
        } catch (Exception e) {

            //try to get it using the 'hostname' command
            String nameFromCommandLine = hostnameFromCommandline();
            if(nameFromCommandLine != null) {
                return nameFromCommandLine;
            } else {
                System.out.println("Problem reading device name at /etc/hostname for OS: {}" + System.getProperty("os.name") +  e.getMessage());
            }
        }
        return "Unnamed";
    }

    private static String hostnameFromCommandline() {       //TODO make this work for Windows?
        String line=null;
        try {
            Runtime rt = Runtime.getRuntime();
            Process pr = rt.exec("hostname");
            BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
            line = input.readLine();
//            while((line=input.readLine()) != null) {
//                System.out.println(line);
//            }
//            int exitVal = pr.waitFor();
        } catch(Exception e) {
            System.out.println(e.toString());
            e.printStackTrace();
        }
        return line;
    }

    // http://stackoverflow.com/a/2406819
    public static boolean isThisMyIpAddress(InetAddress addr) {
        // Check if the address is a valid special local or loop back
        if (addr.isAnyLocalAddress() || addr.isLoopbackAddress())
            return true;

        // Check if the address is defined on any interface
        try {
            return NetworkInterface.getByInetAddress(addr) != null;
        } catch (SocketException e) {
            return false;
        }
    }

    /**
     * Get the broadcast address for a particular network interface
     * @param ni Network Intervace. If we set as NULL, we will use 255.255.255.255
     * @return brodcast address if it exists
     */
    public static InetAddress getBroadcast(NetworkInterface ni)
    {
        InetAddress broadcast = null;

        try {
            if (ni == null)
            {
                broadcast = InetAddress.getByName("255.255.255.255");
            }
            else {
                if (ni.isLoopback()) {
                    broadcast = InetAddress.getByName("localhost");
                } else {
                    for (InterfaceAddress interface_address : ni.getInterfaceAddresses()) {
                        broadcast = interface_address.getBroadcast();
                        if (broadcast != null) {
                            break;
                        }
                    }
                }
            }
        }catch (Exception ex)
        {

        }
        return broadcast;
    }

    public static void main(String[] args) {
        System.out.println(hostnameFromCommandline());
    }
}
