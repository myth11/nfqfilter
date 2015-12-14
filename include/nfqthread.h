/*
*
*    Copyright (C) Max <max1976@mail.ru>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef __NFQTHREAD_H
#define __NFQTHREAD_H

#include <Poco/Task.h>
#include <Poco/Logger.h>

#define T_DATA_SIZE 4096

#define NFQ_BURST_FACTOR 4


struct nfqConfig
{
	int queueNumber;
	int max_pending_packets;
	int mark_value;
	bool send_rst;
	bool save_exception_dump;
	bool block_undetected_ssl;
};

struct threadStats
{
	u_int64_t marked_ssl;
	u_int64_t redirected_domains;
	u_int64_t redirected_urls;
	u_int64_t marked_hosts;
	u_int64_t sended_rst;
};

class nfqThread: public Poco::Task
{
public:
	nfqThread(struct nfqConfig& cfg);
	virtual void runTask();
	static int nfqueue_cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data);
	void getStats(threadStats &);

private:
	Poco::Logger& _logger;
	struct nfq_q_handle *qh;
	int _queue_maxlen;
	struct nfqConfig _config;
	struct threadStats _stats;
	Poco::Mutex _statsMutex;
};

#endif
