#	$OpenBSD: stderr-after-eof.sh,v 1.1 2002/03/23 16:38:09 markus Exp $
#	Placed in the Public Domain.

tid="stderr data after eof"

DATA=/etc/motd
DATA=${OBJ}/data
COPY=${OBJ}/copy

if [ -x "`which md5sum 2>&1`" ]; then
	CHECKSUM=md5sum
elif [ -x "`which openssl 2>&1`" ]; then
	CHECKSUM="openssl md5"
elif [ -x "`which cksum 2>&1`" ]; then
	CHECKSUM=cksum
elif [ -x "`which sum 2>&1`" ]; then
	CHECKSUM=sum
else
	fatal "No checksum program available, aborting $tid test"
fi

# setup data
rm -f ${DATA} ${COPY}
cp /dev/null ${DATA}
for i in 1 2 3 4 5 6; do
	(date;echo $i) | $CHECKSUM >> ${DATA}
done

${SSH} -2 -F $OBJ/ssh_proxy otherhost \
	exec sh -c \'"exec > /dev/null; sleep 2; cat ${DATA} 1>&2 $s"\' \
	2> ${COPY}
r=$?
if [ $r -ne 0 ]; then
	fail "ssh failed with exit code $r"
fi
egrep 'Disconnecting: Received extended_data after EOF' ${COPY} &&
	fail "ext data received after eof"
cmp ${DATA} ${COPY}	|| fail "stderr corrupt"

rm -f ${DATA} ${COPY}
