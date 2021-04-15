#pragma once
#include <QtCore/QVariant>
#include <QtCore/QString>


namespace app
{
    class LocalIniFile
    {
    public:
        /* @fn				�ӳ���Ŀ¼��ini�ļ���ȡ����
         * @brief
         * @param <IN>		qstrSecName			������������
                            strKey				��������
                            qstrFilename		Ŀ�� ini�ļ�����
         * @param <OUT>
         * @return none.	QVariant			�ļ��Ĳ�������  ʧ�ܣ�	QVariant.isValid() return false
         * @date 			2015/7/2 16:04
         */
        static QVariant ReadValue(const QString &qstrSecName, const QString &strKey, const QString& qstrFilename);
        /* @fn				�ӳ���Ŀ¼��ini�ļ���ȡ����
         * @brief
         * @param <IN>		qstrSecName			������������
                            strKey				��������
                            qvValue				д�������
                            qstrFilename		Ŀ�� ini�ļ�����
         * @param <OUT>
         * @return none.	QVariant			�ļ��Ĳ�������  ʧ�ܣ�	QVariant.isValid() return false
         * @date 			2015/7/2 16:04
         */
        static void WriteValue(const QString &strSecName, const QString &strKey, QVariant qvValue, const QString& qstrFilename);
    };
}