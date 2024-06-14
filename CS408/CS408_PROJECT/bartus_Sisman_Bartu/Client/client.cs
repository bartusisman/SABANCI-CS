using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public partial class client : Form
    {
        bool terminating = false;
        bool connected = false;

        Socket clientSocket;

        public client()
        {
            InitializeComponent();
            this.FormClosing += new FormClosingEventHandler(client_FormClosing);

            if100_subscribe_button.Enabled = false;
            sps101_subscribe_button.Enabled = false;
            if100_send_button.Enabled = false;
            sps101_send_button.Enabled = false;
            if100_messages.Enabled = false;
            sps101_messages.Enabled = false;
        }

        private void client_FormClosing(object sender, FormClosingEventArgs e)
        {
            terminating = true;

            if (clientSocket != null && clientSocket.Connected)
            {
                try
                {
                    clientSocket.Send(Encoding.Default.GetBytes("Log out" + name_box.Text)); //send the logout message to server
                }
                catch
                {
                    // exception handling
                }
                finally
                {
                    clientSocket.Shutdown(SocketShutdown.Both); // disable both send and receive activities
                    clientSocket.Close(); 
                }
            }

        }

        private void Handle_Connection() //Manages the connection to the server
        {

            string IP = IP_box.Text;
            int portNum;

            if (string.IsNullOrWhiteSpace(IP) || !Int32.TryParse(port_box.Text, out portNum))
            {
                client_actions.AppendText("Please enter a valid IP and Port to connect.\n");
                return;
            }

            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                clientSocket.Connect(IP, portNum);
                connected = true;
                login_button.Enabled = true;
                port_box.Enabled = false;
                IP_box.Enabled = false;

            }
            catch
            {
                client_actions.AppendText("Could not connect to the server!\n");
            }

        }

        private void DisplayMessage(string message)
        {
            if (message.StartsWith("if100:"))
            {
                if100_messages.AppendText(message.Substring(6) + "\n"); // substract the message and append it to if100 RichTextBox
            }
            else if (message.StartsWith("sps101:"))
            {
                sps101_messages.AppendText(message.Substring(7) + "\n"); //substract the message and append it to sps101 RichTextBox
            }
        }

        private void ReceiveMessage()
        {
            while (connected)
            {
                try
                {
                    byte[] buffer = new byte[1024];
                    int rec = clientSocket.Receive(buffer);

                    if (rec <= 0)
                    {
                        throw new SocketException();
                    }

                    string response = Encoding.Default.GetString(buffer).Trim('\0');

                    if (response == "Name accepted") // if server accepts the name make adjustments in GUI and welcome the client
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            client_actions.AppendText("Welcome " + name_box.Text + "!\n");

                            if100_subscribe_button.Enabled = true;
                            sps101_subscribe_button.Enabled = true;

                            login_button.Text = "Log out";
                            login_button.BackColor = Color.Red;

                            name_box.Enabled = false;
                        });
                    }

                    else if (response.StartsWith("if100:") || response.StartsWith("sps101:")) //if server has a message to deliver to a spesific channel or channels
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            DisplayMessage(response);
                        });
                    }

                    else //any other message from server is displayed in client_actions
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            client_actions.AppendText(response + "\n");
                        });
                    }
                }
                catch
                {
                    if (!terminating)
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            client_actions.AppendText("Lost connection to the server.\n");

                            if100_send_button.Enabled = false;
                            if100_subscribe_button.Enabled = false;
                            sps101_send_button.Enabled = false;
                            sps101_subscribe_button.Enabled = false;
                        });
                    }
                    clientSocket.Close();
                    connected = false;
                }
            }
        }

        private void SendSubscriptionRequest(string channel, bool subscribe) //sends and subscribtion or unsubscribtion message to the server
        {
            string request = (subscribe ? "Subscribe " : "Unsubscribe ") + channel;
            byte[] buffer = Encoding.Default.GetBytes(request);
            clientSocket.Send(buffer);
        }

        private void SendMessageToChannel(string channel, string message) //sends the Message command, which channel and message itself to the server
        {
            string request = $"Message {channel} {message}";
            byte[] buffer = Encoding.Default.GetBytes(request);
            clientSocket.Send(buffer);
        }

        private void login_button_Click(object sender, EventArgs e) //handles what will happen when login_button is clicked
        {
            if (login_button.Text == "Log in")
            {
                Handle_Connection();

                if (connected)
                {
                    if (string.IsNullOrWhiteSpace(name_box.Text))
                    {
                        client_actions.AppendText("Please enter a name!\n");
                    }
                    else 
                    {
                        client_actions.AppendText("You are connected to the server !\n");
                    }

                    byte[] buffer = Encoding.Default.GetBytes(name_box.Text);
                    clientSocket.Send(buffer); // send the name to the server

                    Thread CheckThread = new Thread(ReceiveMessage);
                    CheckThread.Start(); //start the thread to check if name is accepted by the server
                }
            }

            else if (login_button.Text == "Log out")
            {
                // Send a logout message to the server
                if (connected) 
                {
                    byte[] buffer = Encoding.Default.GetBytes("Log out" + name_box.Text); // Logout command
                    clientSocket.Send(buffer);
                }

                this.Close(); // handling closing will be done automatically by client_FormClosing event handler
            }

        }

        private void sps101_subscribe_button_Click(object sender, EventArgs e)
        {
            string channel = "sps101";
            if (sps101_subscribe_button.Text == "Subscribe")
            {
                SendSubscriptionRequest(channel, true); // true for subscribe
                sps101_subscribe_button.Text = "Unsubscribe"; //after subscribing change the button text to unsubscribe this button manages both of the actions
                sps101_subscribe_button.BackColor = Color.Red;
                sps101_send_button.Enabled = true;
            }
            else if (sps101_subscribe_button.Text == "Unsubscribe")
            {
                SendSubscriptionRequest(channel, false); // false for unsubscribe
                sps101_subscribe_button.Text = "Subscribe";
                sps101_subscribe_button.BackColor = Color.Green;
                sps101_send_button.Enabled = false;

            }
        }

        private void if100_subscribe_button_Click(object sender, EventArgs e)
        {
            string channel = "if100";
            if (if100_subscribe_button.Text == "Subscribe")
            {
                SendSubscriptionRequest(channel, true); // true for subscribe
                if100_subscribe_button.Text = "Unsubscribe";
                if100_subscribe_button.BackColor = Color.Red;
                if100_send_button.Enabled = true;
            }
            else if (if100_subscribe_button.Text == "Unsubscribe")
            {
                SendSubscriptionRequest(channel, false); // false for unsubscribe
                if100_subscribe_button.Text = "Subscribe";
                if100_subscribe_button.BackColor = Color.Green;
                if100_send_button.Enabled = false;
            }

        }

        private void if100_send_button_Click(object sender, EventArgs e)
        {
            string message = if100_message_box.Text; 
            SendMessageToChannel("if100", message);
            if100_message_box.Clear();//clear the message box after sending a message

        }

        private void sps101_send_button_Click(object sender, EventArgs e)
        {
            string message = sps101_message_box.Text;
            SendMessageToChannel("sps101", message);
            sps101_message_box.Clear(); //clear the message box after sending a message
        }
    }
}
