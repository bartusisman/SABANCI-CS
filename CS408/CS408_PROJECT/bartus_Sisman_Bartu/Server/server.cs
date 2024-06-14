using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Threading;
using System.Net;

namespace Server
{
    public partial class server : Form
    {
        Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);


        Dictionary<string, Socket> clientSockets = new Dictionary<string, Socket>(); // name of the clients and the sockets
        
        Dictionary<string, List<string>> channelSubscriptions = new Dictionary<string, List<string>>() // subscribers of both channels
        {
            { "if100", new List<string>() },
            { "sps101", new List<string>() }
        };
        Dictionary<string, List<string>> channelMessages = new Dictionary<string, List<string>>() // messages of both channels
        {
            { "if100", new List<string>() },
            { "sps101", new List<string>() }
        };


        Thread listenerThread;

        bool terminating = false;
        bool listening = false;

        public server()
        {
            InitializeComponent();
            this.FormClosing += new FormClosingEventHandler(MainForm_FormClosing);
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Optionally ask the user for confirmation
            if (MessageBox.Show("Are you sure you want to close the server?", "Confirm", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {

                // Close all client sockets
                lock (clientSockets)
                {
                    foreach (var pair in clientSockets)
                    {
                        pair.Value.Close();
                    }
                    clientSockets.Clear();
                }

                terminating = true;

                if (listening)
                {
                    StopListening();
                }

            }
            else
            {
                // If the user does not confirm, cancel the closing event
                e.Cancel = true;
            }
        }

        public void StartListening(int port)
        {
            serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            serverSocket.Bind(new IPEndPoint(IPAddress.Any, port));
            serverSocket.Listen(10); 

            listening = true;
            listenerThread = new Thread(Accept);
            listenerThread.Start();
        }

        public void StopListening()
        {
            listening = false; // signal the Accept loop to stop
            serverSocket.Close(); // this will cause an exception in the Accept call

            if (listenerThread != null && listenerThread.IsAlive)
            {
                listenerThread.Join(); // wait for the listener thread to finish
            }

            lock (clientSockets)
            {
                foreach (var pair in clientSockets) // close all sockets
                {
                    pair.Value.Close();
                }
                clientSockets.Clear(); //empty the dictionary
            }
        }

        private void UpdateRichTextBoxWithList(List<string> items, RichTextBox richTextBox) //empties the spesific richtextbox and adds each item in the items list to the richtextbox
        {
            this.Invoke((MethodInvoker)delegate
            {
                richTextBox.Clear(); // clear the existing content

                foreach (var item in items)
                {
                    richTextBox.AppendText(item.ToString() + "\n"); // add each item in the list to the RichTextBox
                }
            });
        }
        private List<string> GetClientNames() //makes a list out of clientSockets dictionary
        {
            lock (clientSockets)
            {
                return clientSockets.Keys.ToList();
            }
        }
        private void UpdateConnectedClientsUI() // spesific command to update the content of connected_clients richtextbox
        {
            var clientNames = GetClientNames();
            UpdateRichTextBoxWithList(clientNames, connected_clients);
        }

        private string ProcessClientName(string receivedName, Socket clientSocket) // for the input client socket check if the name that was sent by it is valid or not and send the according message to the server
        {
            IPEndPoint remoteEndPoint = clientSocket.RemoteEndPoint as IPEndPoint;
            string clientIP = remoteEndPoint.Address.ToString();

            if (clientSockets.ContainsKey(receivedName))
            {
                byte[] message = Encoding.Default.GetBytes("Name is already taken, try a different name!");
                clientSocket.Send(message);
                return null;
            }
            else
            {
                lock (clientSockets)
                {
                    clientSockets[receivedName] = clientSocket;
                }

                byte[] welcomeMessage = Encoding.Default.GetBytes("Name accepted");

                this.Invoke((MethodInvoker)delegate
                {
                    server_actions.AppendText("IP:" + clientIP);
                    server_actions.AppendText(" Name:" + receivedName + "\n");
                    server_actions.AppendText("Has logged in!\n");

                    UpdateConnectedClientsUI(); // Updates the list and displays it in connected_clients
                });

                clientSocket.Send(welcomeMessage);
                return receivedName;
            }
        }

        private void HandleClientLogout(string message, Socket clientSocket) //if a client logs out remove its all subscriptions and remove its connection from the server and update related richtextboxes
        {
            string nameToLogout = message.Substring(7); // extract the name

            this.Invoke((MethodInvoker)delegate
            {
                if (nameToLogout == "") //if client logs out without entering a name
                {
                    server_actions.AppendText("Anonymous user has logged out.\n");
                }
                else 
                {
                    server_actions.AppendText(nameToLogout + " has logged out.\n");
                }
            });

            lock (clientSockets) //remove all association of client with the server
            {
                if (clientSockets.ContainsKey(nameToLogout))
                {
                    clientSockets.Remove(nameToLogout);
                    UpdateConnectedClientsUI(); // updates the list and displays it in connected_clients
                }
                UnsubscribeClientFromChannel(nameToLogout, "if100");
                UnsubscribeClientFromChannel(nameToLogout, "sps101");

            }
            
            clientSocket.Close(); // close the client socket
        }

        private void BroadcastMessage(string sender, string channel, string message) // sends the message to all subscribers of channel by indicating the name of the sender
        {
            lock (channelMessages)
            {
                if (channelMessages.ContainsKey(channel))
                {
                    string fullMessage = $"{channel}: {sender}: {message}"; // prefixing the message with the channel name
                    channelMessages[channel].Add(fullMessage);

                    lock (channelSubscriptions)
                    {
                        foreach (var clientName in channelSubscriptions[channel]) //send message to each subscribers of spesific channel
                        {
                            lock (clientSockets)
                            {
                                if (clientSockets.TryGetValue(clientName, out Socket clientSocket))
                                {
                                    try
                                    {
                                        byte[] buffer = Encoding.Default.GetBytes(fullMessage);
                                        clientSocket.Send(buffer);
                                    }
                                    catch // catch any errors during sending
                                    {

                                    }
                                }
                            }
                        }
                        this.Invoke((MethodInvoker)delegate
                        {
                            server_actions.AppendText(sender + " sent a message to " + channel.ToUpper() + "\nMessage info: " + message + "\n");
                        });
                    }
                }
            }
        }

        private void SubscribeClientToChannel(string clientName, string channel) // adds subscriptions to spesific channells and displays it in richtextboxes
        {
            lock (channelSubscriptions)
            {
                if (channelSubscriptions.ContainsKey(channel))
                {
                    if (!channelSubscriptions[channel].Contains(clientName))
                    {
                        channelSubscriptions[channel].Add(clientName);

                        if (channel == "if100")
                        {
                            UpdateRichTextBoxWithList(channelSubscriptions[channel], if100_subscribers);
                        }
                        else if (channel == "sps101") 
                        {
                            UpdateRichTextBoxWithList(channelSubscriptions[channel], sps101_subscribers);
                        }
                    }
                }
            }
        }

        private void UnsubscribeClientFromChannel(string clientName, string channel) // removes subscriptions to spesific channells and displays it in richtextboxes
        {
            lock (channelSubscriptions)
            {
                if (channelSubscriptions.ContainsKey(channel) && channelSubscriptions[channel].Contains(clientName))
                {
                    channelSubscriptions[channel].Remove(clientName);

                    if (channel == "if100")
                    {
                        UpdateRichTextBoxWithList(channelSubscriptions[channel], if100_subscribers);
                    }
                    else if (channel == "sps101")
                    {
                        UpdateRichTextBoxWithList(channelSubscriptions[channel], sps101_subscribers);
                    }
                }
            }
        }

        private void ReceiveMessage(Socket clientSocket) //processes all messages sent by the client, Log out, namecheck, subscribe, unsubscribe
        {
            bool connected = true;
            string clientName = null;

            while (connected && !terminating)
            {
                try
                {
                    byte[] buffer = new byte[1024];
                    int rec = clientSocket.Receive(buffer);

                    if (rec <= 0)
                    {
                        throw new SocketException();
                    }

                    string receivedMessage = Encoding.Default.GetString(buffer).Trim('\0');


                    if (receivedMessage.StartsWith("Log out"))
                    {
                        HandleClientLogout(receivedMessage, clientSocket);
                        return; // Exit the function as the client is logging out
                    }

                    else if (clientName == null) // Checking for the client's name
                    {
                        clientName = ProcessClientName(receivedMessage, clientSocket);
                    }

                    else if (receivedMessage.StartsWith("Subscribe "))
                    {
                        string channel = receivedMessage.Split(' ')[1];
                        SubscribeClientToChannel(clientName, channel);

                        this.Invoke((MethodInvoker)delegate
                        {
                            server_actions.AppendText(clientName + " has subscribed to " + channel.ToUpper() + "\n");
                        });
                    }
                    else if (receivedMessage.StartsWith("Unsubscribe "))
                    {
                        string channel = receivedMessage.Split(' ')[1];
                        UnsubscribeClientFromChannel(clientName, channel);

                        this.Invoke((MethodInvoker)delegate
                        {
                            server_actions.AppendText(clientName + " has unsubscribed from " + channel.ToUpper() + "\n");
                        });
                    }

                    else if (receivedMessage.StartsWith("Message "))
                    {
                        string[] parts = receivedMessage.Split(new[] { ' ' }, 3);
                        string channel = parts[1];
                        string message = parts[2];

                        BroadcastMessage(clientName, channel, message);
                    }

                    else
                    {
                        // Handle other messages from client
                    }
                }
                catch
                {
                    if (!terminating)
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            server_actions.AppendText(clientName != null ? $"Client {clientName} has disconnected.\n" : "A client has disconnected.\n");
                        });
                        
                        lock (clientSockets)
                        {
                            if (clientName != null && clientSockets.ContainsKey(clientName))
                            {
                                clientSockets.Remove(clientName);
                                
                            }
                        }
                    }

                    clientSocket.Close();
                    connected = false;
                }
            }
        }

        private void Accept() //constantly listens for clients and navigates their messages
        {
            while (listening)
            {
                try
                {
                    Socket newClient = serverSocket.Accept();

                    Thread receiveThread = new Thread(() => ReceiveMessage(newClient));
                    receiveThread.Start();
                }
                catch
                {
                    if (terminating)
                    {
                        listening = false;
                    }
                    else
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            server_actions.AppendText("The socket stopped working.\n");
                        });
                    }
                }
            }
        }

        private void listen_button_Click(object sender, EventArgs e)
        {
            int serverPort;

            if (Int32.TryParse(port_box.Text, out serverPort))
            {
                StartListening(serverPort);
                listen_button.Enabled = false;

                Thread acceptThread = new Thread(Accept);
                acceptThread.Start();

                server_actions.AppendText("Started listening on port: " + serverPort + "\n");
            }
            else
            {
                server_actions.AppendText("Please check the port number!\n");
            }
        }
    }
}
